#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Transaction.h"

using namespace std;

class Account;
class Language;

class Session {
private:
    Account* current_account; 
    vector<Transaction> session_transactions; 
    int withdrawal_count; 
    long session_id; 
    

public:
    Session(Account* acc, long s_id);
    ~Session();

    Account* getAccount();
    void addTransaction(const Transaction& tx);
    void printSessionSummary(Language* lang) const; 
    
    bool canWithdraw() const; 
    void incrementWithdrawalCount(); 

    int getWithdrawalCount() const;
};

#endif