#ifndef TRANSACTION_H  
#define TRANSACTION_H

#include <string>
#include <ctime>

using namespace std;

class Language;

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};

class Transaction {

private:
    string transaction_id;     
    TransactionType type;               
    long amount;                        
    long fee;                   
    string source_account_number; 
    string destination_account_number; 
    time_t timestamp;    

public:
    Transaction(string tx_id, TransactionType tx_type, long tx_amount, long tx_fee,
                string src_acc, string dest_acc);

    string getTransactionID() const;
    TransactionType getType() const;
    string getTypeString() const; 
    long getAmount() const;
    long getFee() const;
    string getSourceAccountNumber() const;
    string getDestinationAccountNumber() const;
    string getTimestampString() const; 

    string getSummaryString(Language* lang) const;

};

#endif