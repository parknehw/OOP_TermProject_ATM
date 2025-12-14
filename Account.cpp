#include "Account.h"  
#include "Bank.h"     
#include <sstream>   

using namespace std;

Account::Account(Bank* bank, string u_name, string acc_num, 
                 long initial_balance) 
{
    bankName = bank;
    user_name = u_name;
    account_number = acc_num;
    balance = initial_balance;
}

bool Account::deposit(long amount) {
    if (amount <= 0) {
        return false;
    }
    balance += amount;
    return true;
}

void Account::withdraw(long amount) {
    if (canWithdraw(amount)) {
        balance -= amount;
    }
}

bool Account::canWithdraw(long amount) const {
    if (amount <= 0) return false;
    return (balance >= amount);
}

void Account::addTransaction(Transaction tx) {
    transaction_history.push_back(tx);
}

long Account::getBalance() {
    return balance;
}

string Account::getAccountNumber() {
    return account_number;
}

string Account::getUserName() {
    return user_name;
}

string Account::getBankName() {
    return bankName->getBankName();
}

Bank* Account::getBank() {
    return bankName;
}

string Account::getSnapshotString() const{
    stringstream ss;
    ss << "Account [Bank: " << bankName->getBankName() << ", "
       << "No. " << account_number << ", "
       << "Owner: " << user_name << "] "
       << "Balance: " << balance;
    return ss.str();
}