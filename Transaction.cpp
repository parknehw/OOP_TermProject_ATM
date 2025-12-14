#include "Transaction.h"
#include "Language.h"
#include <sstream>  
#include <iomanip>

using namespace std;

Transaction::Transaction(string tx_id, TransactionType tx_type, long tx_amount, long tx_fee,
                         string src_acc, string dest_acc) 
{
    this->transaction_id = tx_id;
    this->type = tx_type;
    this->amount = tx_amount;
    this->fee = tx_fee;
    this->source_account_number = src_acc;
    this->destination_account_number = dest_acc;

    this->timestamp = time(nullptr);
}

string Transaction::getTransactionID() const {
    return transaction_id;
}

TransactionType Transaction::getType() const {
    return type;
}

string Transaction::getTypeString() const {
    switch (type) {
        case TransactionType::DEPOSIT:    return "Deposit";
        case TransactionType::WITHDRAWAL: return "Withdrawal";
        case TransactionType::TRANSFER:   return "Transfer";
        default:                          return "Unknown";
    }
}

long Transaction::getAmount() const {
    return amount;
}

long Transaction::getFee() const {
    return fee;
}

string Transaction::getSourceAccountNumber() const {
    return source_account_number;
}

string Transaction::getDestinationAccountNumber() const {
    return destination_account_number;
}

string Transaction::getSummaryString(Language* lang) const {
    stringstream ss;

    ss << "[" << lang->getLabelTransactionID() << ": " << transaction_id << "] ";

    switch (type) {
        case TransactionType::DEPOSIT:
            ss << lang->getSummaryDeposit(amount, destination_account_number, fee);
            break;
        case TransactionType::WITHDRAWAL:
            ss << lang->getSummaryWithdrawal(amount, source_account_number, fee);
            break;
        case TransactionType::TRANSFER:
            ss << lang->getSummaryTransfer(amount, source_account_number, 
                                          destination_account_number, fee);
            break;
    }
    return ss.str();
}