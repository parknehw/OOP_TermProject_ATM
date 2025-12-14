#include "ATM.h"
#include "BankManager.h"
#include "Session.h"
#include "Account.h"
#include "Bank.h"
#include "Card.h"
#include "DebitCard.h"
#include "AdminCard.h"
#include "KoreanLanguage.h"
#include "EnglishLanguage.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

ATM::ATM(string serial, Bank* primary, string type_str, 
         string lang_str, string cash_str, BankManager* manager)
    : serial_number(serial), primary_bank(primary), bankManager(manager),
      current_language(nullptr), session_counter(0)
{
    if (type_str == "Single") {
        atm_type = ATMType::SINGLE_BANK;
    } else {
        atm_type = ATMType::MULTI_BANK;
    }

    english_lang = make_unique<EnglishLanguage>();
    if (lang_str == "Unilingual") {
        language_support = ATMLanguage::UNILINGUAL;
        current_language = english_lang.get();
    } else {
        language_support = ATMLanguage::BILINGUAL;
        korean_lang = make_unique<KoreanLanguage>();
    }

    parseInitialCash(cash_str);
}

ATM::~ATM() {
}

void ATM::setAllBanks(const vector<Bank*>& banks) {
    this->all_banks = banks;
}

void ATM::start() {
    cout << "\n=============================================" << endl;
    cout << "=== " << primary_bank->getBankName() << " ATM (SN: " << serial_number << ") ===" << endl;

    if (language_support == ATMLanguage::BILINGUAL) {
        selectLanguage();
    }
    
    cout << current_language->getGreeting() << endl;
    cout << current_language->getInsertCard() << endl;

    this->session_counter++;

    Session* session = authenticateUser();

    if (session != nullptr) {
        runUserSession(session);
        session->printSessionSummary(current_language);
        delete session;
    }
    
    cout << "=============================================\n" << endl;
    
    if (language_support == ATMLanguage::BILINGUAL) {
        current_language = nullptr;
    }
}

string ATM::getSnapshotString() const {
    stringstream ss;
    long total_cash = 0;
    for (auto const& [denomination, count] : cash_bin) {
        total_cash += denomination * count;
    }

    ss << primary_bank->getBankName() << " ATM [SN:" << serial_number << "] Remaining cash: " << total_cash << " | Left cash ";
    ss << "(Total Sessions: " << session_counter << ") ";  
    ss << cash_bin.at(1000) << " x 1,000 won, ";
    ss << cash_bin.at(5000) << " x 5,000 won, ";
    ss << cash_bin.at(10000) << " x 10,000 won, ";
    ss << cash_bin.at(50000) << " x 50,000 won";
    return ss.str();
}

void ATM::runUserSession(Session* session) {
    bool running = true;
    while (running) {
        cout << "\n" << current_language->getMainMenu() << endl;
        cout << current_language->getSelectionPrompt(); 
        string input;
        cin >> input;
             
        if (input=="/") {
                 bankManager->printAllSnapshots();
                 continue;
        }

        int choice;
        try {
                 choice=stoi(input);
        } catch (const std::invalid_argument&) {
                 choice = -1;
        } catch (const std::out_of_range&) {
                 choice = -1;
        }

        switch (choice) {
            case 1: {
                if (!performDeposit(session)){
                    running = false;
                }
                break;
            }
            case 2: {
                if (!performWithdrawal(session)) {
                    running = false;
                }
                break;
            }
            case 3: {
                if (!performTransfer(session)) {
                    running = false;
                }
                break;
            }
            case 4: {
                cout << current_language->getEndSessionPrompt() << endl;
                running = false;
                break;
            }
            default:
                cout << current_language->getInvalidSelection() << endl; 
                choice = -1;
                break;
        }
    }
}

void ATM::runAdminSession() {
    cout << current_language->getAdminModeHeader() << endl; 
    cout << current_language->getAdminMenu();
    string input;
    cin >> input;
    
    int choice = 0; 
    try {
        choice = stoi(input); 
    } catch (const std::invalid_argument&) { 
        choice = -1; 
    } catch (const std::out_of_range&) { 
        choice = -1;
    }

    if (choice == 1) {
        printTotalTransactionHistory();
    }
}

void ATM::selectLanguage() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;

    while (current_language == nullptr) {
        cout << "\nChoose language (언어를 선택하세요): \n1. English \n2. 한국어 \nSelect(선택): ";
        getline(cin, input);
       
        if (input == "1") {
            current_language = english_lang.get();
        } else if (input == "2") {
            current_language = korean_lang.get();
        } else {
            cout << "Invalid choice. (유효하지 않은 선택입니다.)" << endl;
        }
    }
}

Session* ATM::authenticateUser() {
    cout << current_language->getCardNumberPrompt();
    string card_num;
    cin >> card_num;

    Card* card = bankManager->getCardByNumber(card_num);

    if (card == nullptr) {
        cout << current_language->getInvalidCard() << endl;
        return nullptr;
    }

    CardType type = card->getType();
    
    if (type == CardType::DEBIT_CARD) {
        DebitCard* dc = static_cast<DebitCard*>(card);
        Account* acc = dc->getAccount();

        if (!isCardValid(acc->getBank()->getBankName())) {
            cout << current_language->getInvalidCard() << endl;
            return nullptr;
        }
    }
         
    for (int i = 0; i < 3; ++i) {
        cout << current_language->getEnterPassword() << " ";
        string pw;
        cin >> pw;

        if (card->validatePassword(pw)) {
            
            if (type == CardType::ADMIN_CARD) {
                AdminCard* admin_card = static_cast<AdminCard*>(card);

                if (admin_card->getManagingBank() == this->primary_bank) {     
                         runAdminSession();
                         return nullptr; 
                } else {
                         cout << current_language->getInvalidCard() << endl;
                         return nullptr;
                }
            
            } else if (type == CardType::DEBIT_CARD) {
                DebitCard* dc = static_cast<DebitCard*>(card);
                Account* acc = dc->getAccount();
                
                cout << current_language->getWelcomeUser(acc->getUserName()) << endl; 
                
                return new Session(acc, this->session_counter); 
            }
        
        } else {
            cout << current_language->getWrongPassword() << " (" << (i + 1) << "/3)" << endl;
        }
    }

    cout << current_language->getCardBlocked() << endl;
    return nullptr;
}

bool ATM::performDeposit(Session* session) {
    cout << current_language->getDepositMenu() << endl;
    cout << current_language->getSelectionPrompt(); 
    string input;
    cin >> input;
    
    if (input == "/") {
             bankManager->printAllSnapshots();
             return true;
    }    

    int choice = 0; 
    try {
        choice = stoi(input); 
    } catch (const std::invalid_argument&) { 
        choice = -1; 
    } catch (const std::out_of_range&) { 
        choice = -1;
    }
         
    long amount = 0;
    bool is_check = false;
    map<int, int> deposited_bills;

    if (choice == 1) {
        amount = acceptCashInput(50, deposited_bills);
    } else if (choice == 2) {
        amount = acceptCheck();
        is_check = true;
    } else {
        cout << current_language->getInvalidSelection() << endl; 
        return true;
    }

    if (amount == 0) {
        return true;
    }

    long fee = calculateFee(TransactionType::DEPOSIT, session->getAccount());

    if (fee > 0) {
        cout << current_language->getDepositFeePrompt(fee) << endl; 
        while (true) {
            cout << current_language->getConfirmationPrompt();
            string confirm_input;
            cin >> confirm_input;

            ConfirmationResponse response = current_language->checkConfirmation(confirm_input);

            if (response == ConfirmationResponse::YES) {
                break;
            } 
            else if (response == ConfirmationResponse::NO) {
                cout << current_language->getTransactionCancelled() << endl;
                if (!is_check && amount > 0) {
                    cout << current_language->getReturnDepositCash(amount) << endl;
                    vector<int> denoms = {50000, 10000, 5000, 1000};
                    for (int d : denoms) {
                        if (deposited_bills[d] > 0) {
                            cout << current_language->getDispensingCashLine(d, deposited_bills[d]) << endl;
                        }
                    }
                    cout << "-----------------------" << endl;
                }
                return true;
            } 
            else {
                cout << current_language->getInvalidSelection() << endl; 
            }
        }

        cout << current_language->getFeeCashPrompt() << endl;
    } else {
        cout << current_language->getFeeInform(fee) << endl; 
    }
         
    map<int, int> fee_bills;
    long fee_paid = 0;

    if (fee > 0) {
        fee_paid = acceptCashInput(50, fee_bills); 

        if (fee_paid < fee) {
            cout << current_language->getInsufficientFee() << endl; 
            cout << current_language->getReturnFeeCash(fee_paid) << endl;
            if (fee_paid > 0 && !dispenseCash(fee_paid)) {
                 cout << current_language->getCriticalDispenseError() << endl;
            }

            if (!is_check) {
                cout << current_language->getReturnDepositCash(amount) << endl;
                
                if (!dispenseCash(amount)) {
                    cout << current_language->getCriticalDispenseError() << endl;
                }
            }
            return false;
        }
    }

    addBillsToCashBin(fee_bills);
         
    if (fee_paid > fee) {
        long change = fee_paid - fee;
        cout << current_language->getReturningChange(change) << endl; 
        if (!dispenseCash(change)) {
             cout << current_language->getDispenseChangeError() << endl; 
             return false;
        }
    }
    
    if (!is_check) {
        addBillsToCashBin(deposited_bills);
    }

    session->getAccount()->deposit(amount);
    cout << current_language->getTransactionSuccess() << endl;

    createAndAddTransaction(session, TransactionType::DEPOSIT, amount, fee, 
                            nullptr, session->getAccount());
    return true;
}

bool ATM::performWithdrawal(Session* session) {

    if (session->getWithdrawalCount() >= 3) {
        cout << current_language->getSessionWithdrawalLimitExceeded() << endl;
        return false;
    }
    
    long amount = 0;
    while (true)
    {
        cout << current_language->getWithdrawAmountPrompt();
        string amount_input;
        cin >> amount_input;
        
        try {
            amount = stoll(amount_input);
        } catch (const std::invalid_argument&) { 
            cout << current_language->getInvalidAmount() << endl;
            continue;
        } catch (const std::out_of_range&) { 
            cout << current_language->getAmountOutOfRange() << endl;
            continue;
        }

        if (amount <= 0) {
            cout << current_language->getInvalidAmount() << endl;
            continue;
        }
        
        break;
    }

    if (amount > 500000) {
        cout << current_language->getWithdrawAmountLimitExceeded() << endl;
        return false;
    }

    long fee = calculateFee(
        TransactionType::WITHDRAWAL, 
        session->getAccount(),
        nullptr
    );

    cout << current_language->getFeeInform(fee) << endl;

    while (true) {
        cout << current_language->getConfirmationPrompt();
        string input;
        cin >> input;

        ConfirmationResponse response = current_language->checkConfirmation(input);

        if (response == ConfirmationResponse::YES) {
            break; 
        } 
        else if (response == ConfirmationResponse::NO) {
            cout << current_language->getTransactionCancelled() << endl;
            return true; 
        } 
        else {
            cout << current_language->getInvalidSelection() << endl; 
        }
    }

    long total_needed = amount + fee;
    if (!session->getAccount()->canWithdraw(total_needed)) {
        cout << current_language->getInsufficientFunds() << endl;
        return false;
    }
    if (!dispenseCash(amount)) {
        cout << current_language->getInsufficientATMChash() << endl;
        return false;
    }

    session->getAccount()->withdraw(total_needed);

    session->incrementWithdrawalCount(); 

    createAndAddTransaction(session, TransactionType::WITHDRAWAL, amount, fee,
                            session->getAccount(), nullptr);
    
    cout << current_language->getTransactionSuccess() << endl;
    return true;
}

bool ATM::performTransfer(Session* session) {
    cout << current_language->getTransferMenu() << endl;
    cout << current_language->getSelectionPrompt(); 
    string input;
    cin >> input;
    
    int transfer_choice = 0;
    try {
        transfer_choice = stoi(input);
    } catch (const std::invalid_argument&) {
        transfer_choice = -1;
    } catch (const std::out_of_range&) {
        transfer_choice = -1;
    }   


    if (transfer_choice == 1) {
        cout << current_language->getCashTransferHeader() << endl;
        cout << current_language->getDestinationAccountPrompt();
        string dest_acc_num;
        cin >> dest_acc_num;
         
        Account* dest_account = bankManager->findAccountByNumber(dest_acc_num);

        if (dest_account == nullptr) {
            cout << current_language->getDestAccountNotFound() << endl; 
            return true;
        }

        const long fee = 2000;
        cout << current_language->getFeePrompt(fee) << endl;

        map<int, int> inserted_bills;
        
        long inserted = acceptCashInput(50, inserted_bills); 

        if (inserted <= fee) {
            cout << current_language->getTransferAmountError() << endl; 
            if (inserted > 0) {
                cout << "Returning inserted cash: " << inserted << " KRW" << endl;
                if (!dispenseCash(inserted)) {
                     cout << "CRITICAL ERROR: Failed to dispense cash." << endl;
                }
            }
            return false; 
        }

        long amount_to_transfer = inserted - fee;

        addBillsToCashBin(inserted_bills);
             
        dest_account->deposit(amount_to_transfer);

        createAndAddTransaction(session, TransactionType::TRANSFER, 
                                amount_to_transfer, 
                                fee,
                                session->getAccount(),
                                dest_account);
                                    
        cout << current_language->getTransactionSuccess() << endl;
        return true;

    } else if (transfer_choice == 2) {
        cout << current_language->getAccountTransferHeader() << endl;

        cout << current_language->getDestinationAccountPrompt();
        string dest_acc_num;
        cin >> dest_acc_num;
         
        Account* dest_account = bankManager->findAccountByNumber(dest_acc_num);

        if (dest_account == nullptr) {
            cout << current_language->getDestAccountNotFound() << endl; 
            return true;
        }
        
        cout << current_language->getTransferAmountPrompt();
        string amount_input;
        cin >> amount_input;
        
        long amount = 0;
        try {
            amount = stoll(amount_input); 
        } catch (const std::invalid_argument&) { 
            cout << current_language->getInvalidAmount() << endl;
            return true;
        } catch (const std::out_of_range&) { 
            cout << current_language->getAmountOutOfRange() << endl;
            return true;
        }

        if (amount <= 0) {
            cout << current_language->getInvalidAmount() << endl; 
            return true;
        }
        
        Account* src_account = session->getAccount();

        long fee = calculateFee(
            TransactionType::TRANSFER, 
            src_account, 
            dest_account 
        );

        cout << current_language->getFeeInform(fee) << endl;

        while (true) {
        cout << current_language->getConfirmationPrompt();
        string input;
        cin >> input;

        ConfirmationResponse response = current_language->checkConfirmation(input);

        if (response == ConfirmationResponse::YES) {
            break; 
        } 
        else if (response == ConfirmationResponse::NO) {
            cout << current_language->getTransactionCancelled() << endl;
            return true; 
        } 
        else {
            cout << current_language->getInvalidSelection() << endl; 
        }
    }

        long total_deduct = amount + fee;
             
        if (!src_account->canWithdraw(total_deduct)) {
            cout << current_language->getInsufficientFunds() << endl;
            return false;
        }

        src_account->withdraw(total_deduct);
        dest_account->deposit(amount);

        createAndAddTransaction(session, TransactionType::TRANSFER, amount, fee,
                                src_account, dest_account);

        cout << current_language->getTransactionSuccess() << endl;
        return true;
        
    } else {
        cout << current_language->getInvalidSelection() << endl; 
        return true;
    }
}

long ATM::acceptCashInput(int limit, map<int, int>& bills) {
    long total_amount = 0;
    int total_count = 0;
    bills[50000] = 0; bills[10000] = 0; bills[5000] = 0; bills[1000] = 0;

    cout << current_language->getCashCountPrompt(50000) << " ";
    string input_50k;
    cin >> input_50k;
    
    int c50k = 0;
    try {
        c50k = stoi(input_50k);
    } catch (const std::invalid_argument&) {
        c50k = -1;
    } catch (const std::out_of_range&) {
        c50k = -1; 
    }   

    if (c50k < 0) {
        cout << current_language->getInvalidAmount() << endl; 
        return 0;
    }
    total_count += c50k;
    
    cout << current_language->getCashCountPrompt(10000) << " ";
    string input_10k;
    cin >> input_10k;

    int c10k = 0;
    try {
        c10k = stoi(input_10k);
    } catch (const std::invalid_argument&) {
        c10k = -1;
    } catch (const std::out_of_range&) {
        c10k = -1;
    }

    if (c10k < 0) {
        cout << current_language->getInvalidAmount() << endl;
        return 0;
    }
    total_count += c10k;
    
    cout << current_language->getCashCountPrompt(5000) << " ";
    string input_5k;
    cin >> input_5k;

    int c5k = 0;
    try {
        c5k = stoi(input_5k);
    } catch (const std::invalid_argument&) {
        c5k = -1;
    } catch (const std::out_of_range&) {
        c5k = -1;
    }

    if (c5k < 0) {
        cout << current_language->getInvalidAmount() << endl;
        return 0;
    }
    total_count += c5k;
    
    cout << current_language->getCashCountPrompt(1000) << " ";
    string input_1k;
    cin >> input_1k;

    int c1k = 0;
    try {
        c1k = stoi(input_1k);
    } catch (const std::invalid_argument&) {
        c1k = -1;
    } catch (const std::out_of_range&) {
        c1k = -1;
    }

    if (c1k < 0) {
        cout << current_language->getInvalidAmount() << endl;
        return 0;
    }
    total_count += c1k;

    if (total_count > limit) {
        cout << current_language->getDepositLimitExceeded() << endl;
        return 0;
    }

    bills[50000] = c50k;
    bills[10000] = c10k;
    bills[5000]  = c5k;
    bills[1000]  = c1k;
         
    total_amount = (c50k * 50000) + (c10k * 10000) + (c5k * 5000) + (c1k * 1000);
    if (total_amount == 0) {
        cout << current_language->getInvalidAmount() << endl; 
    }
    return total_amount;
}

long ATM::acceptCheck() {
    cout << current_language->getCheckCountPrompt(30); 
    string input_count;
    cin >> input_count;
    
    int count = 0;
    try {
        count = stoi(input_count);
    } catch (const std::invalid_argument&) {
        count = -1;
    } catch (const std::out_of_range&) {
        count = -1;
    }   

    if (count > 30) {
        cout << current_language->getDepositLimitExceeded() << endl;
        return 0;
    }
    if (count <= 0) {
        cout << current_language->getTransactionCancelled() << endl; 
        return 0;
    }

    long total_amount = 0;
    for (int i = 0; i < count; ++i) {
        cout << current_language->getCheckAmountPromptIndexed(i + 1); 
        string input_amount;
        cin >> input_amount;
        
        long amount = 0;
        try {
            amount = stoll(input_amount); 
        } catch (const std::invalid_argument&) { 
            cout << current_language->getInvalidCheckAmount() << endl; 
            i--;
            continue;
        } catch (const std::out_of_range&) { 
            cout << current_language->getAmountOutOfRange() << endl;
            i--;
            continue;
        }

        if (amount < 100000) {
            cout << current_language->getInvalidCheckAmount() << endl; 
            i--;
        } else {
            total_amount += amount;
        }
    }
    
    cout << current_language->getCheckTotalAmount(total_amount) << endl; 
    return total_amount;
}

void ATM::addBillsToCashBin(const map<int, int>& bills) {
    for (auto const& [denom, count] : bills) {
        if (count > 0) {
            cash_bin[denom] += count;
        }
    }
}

bool ATM::dispenseCash(long amount) {
    long remaining = amount;
    map<int, int> to_dispense;
    vector<int> denominations = {50000, 10000, 5000, 1000};
    for (int denom : denominations) {
        int count_needed = remaining / denom;
        if (count_needed > 0) {
            int count_available = cash_bin[denom];
            int count_to_use = min(count_needed, count_available);
            to_dispense[denom] = count_to_use;
            remaining -= count_to_use * denom;
        }
    }

    if (remaining != 0) {
        return false;
    }

    cout << current_language->getDispensingCashHeader() << endl; 
    for (auto const& [denom, count] : to_dispense) {
        if (count > 0) {
            cash_bin[denom] -= count;
            cout << current_language->getDispensingCashLine(denom, count) << endl; 
        }
    }
    cout << "-----------------------" << endl;
    return true;
}

long ATM::calculateFee(TransactionType type, Account* session_account, 
                      Account* dest_account, bool is_cash_transfer) 
{
    bool is_primary_session = (session_account->getBank() == this->primary_bank);

    switch (type) {
        case TransactionType::DEPOSIT: {
            return is_primary_session ? 0 : 1000;
        }

        case TransactionType::WITHDRAWAL: {
            return is_primary_session ? 1000 : 2000;
        }

        case TransactionType::TRANSFER: {
            if (is_cash_transfer) {
                return 2000;
            }
                 
            if (dest_account == nullptr) {
                return 0;
            }
            bool is_primary_dest = (dest_account->getBank() == this->primary_bank);

            if (is_primary_session && is_primary_dest) {
                return 1000;
            }
                 
            if (!is_primary_session && !is_primary_dest) {
                return 4000;
            }
                 
            return 2000;
            }
        default: {
            return 0;
        }
    }
}

void ATM::createAndAddTransaction(Session* session, TransactionType type, long amount, long fee, Account* src, Account* dest) {
    string tx_id = bankManager->generateTransactionID();
    string src_acc_num = (src) ? src->getAccountNumber() : "";
    string dest_acc_num = (dest) ? dest->getAccountNumber() : "";

    Transaction tx(tx_id, type, amount, fee, src_acc_num, dest_acc_num);

    total_transaction_history.push_back(tx);
    session->addTransaction(tx);
    if (src) src->addTransaction(tx);
    if (dest) dest->addTransaction(tx);
}

void ATM::printTotalTransactionHistory() {
    string filename = primary_bank->getBankName() + "_" + serial_number + "_history.txt";
    ofstream outfile(filename);

    cout << current_language->getHistoryHeader() << endl; 
    outfile << current_language->getHistoryHeader() << endl;

    for (const auto& tx : total_transaction_history) {
        string log = tx.getSummaryString(current_language);
        cout << log << endl;
        outfile << log << endl;
    }
    
    outfile.close();
    cout << current_language->getHistorySaved(filename) << endl; 
}

bool ATM::isCardValid(const string& card_bank_name) {
    if (atm_type == ATMType::SINGLE_BANK) {
        return card_bank_name == primary_bank->getBankName();
    }
    return true;
}

void ATM::parseInitialCash(const string& cash_str) {
  
    stringstream ss(cash_str);
    int c50k = 0;
    int c10k = 0;
    int c5k = 0;
    int c1k = 0;

    if (ss >> c50k >> c10k >> c5k >> c1k) {
        cash_bin[50000] = c50k;
        cash_bin[10000] = c10k;
        cash_bin[5000] = c5k;
        cash_bin[1000] = c1k;
    } else {
        cerr << "Warning: Could not parse cash string '" << cash_str 
                  << "' for ATM " << serial_number << ". Defaulting to 0 cash." << endl;
        
        cash_bin[50000] = 0;
        cash_bin[10000] = 0;
        cash_bin[5000] = 0;
        cash_bin[1000] = 0;
    }
}

string ATM::getSerialNumber() const {
    return this->serial_number;
}