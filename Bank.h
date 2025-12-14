#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <map>      
#include <memory>   
#include "Account.h" 

using namespace std;

class Bank {

private:
    string bank_name;

    vector<unique_ptr<Account>> all_accounts;

    map<string, Account*> accounts_by_number;

public:
    
    Bank(string name);
    ~Bank(); 

    Account* createAccount(string u_name, string acc_num, 
                       long initial_balance);

    Account* findAccountByNumber(string account_number);

    string getBankName();

    const vector<unique_ptr<Account>>& getAllAccounts() const;
};

#endif