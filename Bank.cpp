#include "Bank.h" 
#include <iostream> 
#include <string> 
#include <memory>  

using namespace std;

Bank::Bank(string name) {
    this->bank_name = name;
}

Bank::~Bank() {
}

Account* Bank::createAccount(string u_name, string acc_num, 
                         long initial_balance) 
{
    auto new_account = make_unique<Account>(
        this, u_name, acc_num, initial_balance);

    Account* account_ptr = new_account.get();

    all_accounts.push_back(std::move(new_account));

    accounts_by_number[acc_num] = account_ptr;

    return account_ptr;
}

Account* Bank::findAccountByNumber(string account_number) {
   
    if (accounts_by_number.count(account_number) > 0) {
    
        return accounts_by_number[account_number];
    }
  
    return nullptr;
}

string Bank::getBankName() {
    return bank_name;
}

const vector<unique_ptr<Account>>& Bank::getAllAccounts() const {
    return all_accounts;
}