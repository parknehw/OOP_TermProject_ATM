#include "BankManager.h"
#include "Bank.h"
#include "Account.h"
#include "Card.h"         
#include "DebitCard.h"    
#include "AdminCard.h"   
#include "ATM.h"          

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>      
#include <stdexcept>   

using namespace std;

BankManager::BankManager() : transaction_id_counter(0) {
    
}

BankManager::~BankManager() {
   
}

void BankManager::run() {
   
    if (!loadInitialData("initial_condition.txt")) {
        cerr << "Error: Failed to load initial data file." << endl;
        return;
    }
    cout << "System data loaded successfully." << endl;

    string input;
    while (true) {
        cout << "\n--------------------------------------------------" << endl;
        cout << "Select ATM (1-" << all_atms.size() << ") | Enter '/' for Snapshot | Enter 'Q' to Quit" << endl;
        cout << "Enter command: ";
        cin >> input;

        if (input == "/") {
            printAllSnapshots(); 
        
        } else if (input == "Q" || input == "q") {
            break; 
        
        } else {
            
            try {
                int atm_index = stoi(input) - 1;
                if (atm_index >= 0 && atm_index < all_atms.size()) {
                    
                    all_atms[atm_index]->start(); 
                
                } else {
                    cout << "Invalid ATM number. Please try again." << endl;
                }
            } catch (invalid_argument&) {
                cout << "Invalid input. Please try again." << endl;
            } catch (const std::out_of_range&) {
                cout << "Invalid input (number too large). Please try again." << endl;
            }
        }
    }
}

bool BankManager::loadInitialData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << filename << endl;
        return false;
    }

    string line;
    int bank_count, account_count, atm_count;

    
    if (!(file >> bank_count >> account_count >> atm_count)) return false;
    getline(file, line); 
    
    if (!loadBanks(file, bank_count)) return false;

    if (!loadAccounts(file, account_count)) return false;

    if (!loadATMs(file, atm_count)) {
        return false;
    }

    vector<Bank*> bank_pointers;
    for (const auto& bank : all_banks) {
        bank_pointers.push_back(bank.get());
    }

    for (const auto& atm : all_atms) {
        atm->setAllBanks(bank_pointers);
    }

    return true;
}

string BankManager::generateTransactionID() {
    transaction_id_counter++; 
    return to_string(transaction_id_counter);
}

Card* BankManager::getCardByNumber(const string& card_number) {
    if (card_map_by_number.count(card_number) > 0) {
        return card_map_by_number[card_number];
    }
    return nullptr;
}

void BankManager::printAllSnapshots() {
    cout << "\n========== [System Snapshot] ==========" << endl;

    cout << "\n--- ATM Status (" << all_atms.size() << ") ---" << endl;
    for (const auto& atm : all_atms) {
        cout << atm->getSnapshotString() << endl;
    }

    cout << "\n--- Account Status ---" << endl;
    for (const auto& bank : all_banks) {
        const auto& accounts = bank->getAllAccounts();
        for (const auto& account : accounts) {
            cout << account->getSnapshotString() << endl;
        }
    }
    cout << "=========================================" << endl;
}

bool BankManager::loadBanks(ifstream& file, int bank_count) {
    string line;
    for (int i = 0; i < bank_count; ++i) {
        if (!getline(file, line)) return false; 

        auto new_bank = make_unique<Bank>(line); 
        bank_map_by_name[line] = new_bank.get(); 
        all_banks.push_back(std::move(new_bank)); 
    }
    return true;
}

bool BankManager::loadAccounts(ifstream& file, int account_count) {
    string line;
    for (int i = 0; i < account_count; ++i) {
        
        string bank_name, user_name, acc_num, card_num, card_pw;
        long balance;

        if (!getline(file, bank_name)) return false;  
        if (!getline(file, user_name)) return false;  
        if (!getline(file, acc_num)) return false;  
        if (!(file >> balance)) return false;  
        getline(file, line);
        if (!getline(file, card_num)) return false;  
        if (!getline(file, card_pw)) return false;  

        if (user_name.find("Admin") != string::npos) {
            
            if (bank_map_by_name.count(bank_name) == 0) {
                cerr << "Error: Bank '" << bank_name << "' not found for Admin Card: " << card_num << endl;
                return false;
            }
            Bank* bank = bank_map_by_name[bank_name];
            auto new_card = make_unique<AdminCard>(card_num, card_pw, bank);
            
            card_map_by_number[card_num] = new_card.get();
            all_cards.push_back(std::move(new_card));

        } else {
            if (bank_map_by_name.count(bank_name) == 0) {
                std::cerr << "Error: Bank not found for account: " << acc_num << std::endl;
                return false;
            }
            Bank* bank = bank_map_by_name[bank_name];

            Account* new_account = bank->createAccount(user_name, acc_num, balance);
            if (new_account == nullptr) {
                return false; 
            }

            auto new_card = make_unique<DebitCard>(card_num, card_pw, new_account);
            
            card_map_by_number[card_num] = new_card.get();
            all_cards.push_back(std::move(new_card));
        }
    }
    return true;
}


bool BankManager::loadATMs(ifstream& file, int atm_count) {
    string line;
    for (int i = 0; i < atm_count; ++i) {
        string primary_bank_name, serial_num, type_str, lang_str, cash_str;

        if (!getline(file, primary_bank_name)) return false;
        
        if (!getline(file, serial_num)) return false;


        if (serial_num.length() != 6) {
            cerr << "Error: Invalid serial number length. Must be 6 digits: " << serial_num << endl;
            return false; 
        }

        for (const auto& atm : all_atms) {
            if (atm->getSerialNumber() == serial_num) {
                cerr << "Error: Duplicate serial number detected: " << serial_num << endl;
                return false; 
            }
        }

        if (!getline(file, type_str)) return false;
        if (!getline(file, lang_str)) return false;
        if (!getline(file, cash_str)) return false;

        if (bank_map_by_name.count(primary_bank_name) == 0) {
            cerr << "Error: Primary bank not found for ATM: " << serial_num << endl;
            return false;
        }
        Bank* primary_bank = bank_map_by_name[primary_bank_name];

        auto new_atm = make_unique<ATM>(
            serial_num, primary_bank, type_str, lang_str, cash_str, this
        );

        all_atms.push_back(std::move(new_atm)); 
    }
    return true;
}

Account* BankManager::findAccountByNumber(const string& acc_num) {
    for (const auto& bank : all_banks) {
        Account* found_account = bank->findAccountByNumber(acc_num);

        if (found_account != nullptr) {
            return found_account; 
        }
    }

    return nullptr;
}
