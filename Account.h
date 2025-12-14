#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Bank;

using namespace std;

class Account {
private:
    Bank* bankName;
    string user_name;
    string account_number;
    long balance;
    vector<Transaction> transaction_history;

public:
    Account(Bank* bank, string u_name, string acc_num, 
            long initial_balance);

    bool deposit(long amount);                  
    void withdraw(long amount); 
    void addTransaction(Transaction tx);
    bool canWithdraw(long amount) const;

    long getBalance();                 
    string getAccountNumber();     
    string getUserName();         
    string getBankName();         
    Bank* getBank();

    string getSnapshotString() const;

};

#endif