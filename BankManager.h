#ifndef BANKMANAGER_H  
#define BANKMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory> 
#include <fstream> 
using namespace std;

class Bank;
class ATM;
class Card;
class Account;

class BankManager {

private:
    vector<unique_ptr<Bank>> all_banks;
    vector<unique_ptr<ATM>> all_atms;
    vector<unique_ptr<Card>> all_cards;

    map<string, Bank*> bank_map_by_name;
    map<string,Card*> card_map_by_number;

    long transaction_id_counter;

    bool loadBanks(ifstream& file, int bank_count);
    bool loadAccounts(ifstream& file, int account_count);
    bool loadATMs(ifstream& file, int atm_count);

public:
    BankManager();
    ~BankManager(); 

    bool loadInitialData(const string& filename);

    void run();

    Card* getCardByNumber(const string& card_number);
    string generateTransactionID();

    void printAllSnapshots();
    Account* findAccountByNumber(const string& acc_num);
};

#endif 