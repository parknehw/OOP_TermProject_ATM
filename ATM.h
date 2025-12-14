#ifndef ATM_H
#define ATM_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Transaction.h"
#include "Language.h"

using namespace std;

class Bank;
class BankManager;
class Account;
class Card;
class Session;

enum class ATMType {
    SINGLE_BANK,
    MULTI_BANK
};

enum class ATMLanguage {
    UNILINGUAL,
    BILINGUAL
};


class ATM {

private:
    string serial_number;
    Bank* primary_bank;
    BankManager* bankManager;
    
    ATMType atm_type;
    ATMLanguage language_support;

    map<int, int> cash_bin;

    vector<Transaction> total_transaction_history;

    vector<Bank*> all_banks;

    Language* current_language;
    unique_ptr<Language> english_lang;
    unique_ptr<Language> korean_lang;

    long session_counter;

public:
    ATM(string serial, Bank* primary, string type_str, 
        string lang_str, string cash_str, BankManager* manager);

    ~ATM();

    void setAllBanks(const vector<Bank*>& banks);

    void start();

    string getSnapshotString() const;

    string getSerialNumber() const;

private:
    void runUserSession(Session* session);
    void runAdminSession();

    void selectLanguage();
    Session* authenticateUser();

    bool performDeposit(Session* session);
    bool performWithdrawal(Session* session);
    bool performTransfer(Session* session);

    long acceptCashInput(int limit, map<int, int>& bills);
    long acceptCheck();
    void addBillsToCashBin(const map<int, int>& bills);

    bool dispenseCash(long amount);
    
    long calculateFee(TransactionType type, Account* session_account, 
                      Account* dest_account = nullptr, bool is_cash_transfer = false);

    void createAndAddTransaction(Session* session, TransactionType type, long amount, long fee, Account* src, Account* dest);

    void printTotalTransactionHistory();
    bool isCardValid(const string& card_bank_name);
    
    void parseInitialCash(const string& cash_str);
    long acceptCash(int limit);
};

#endif 