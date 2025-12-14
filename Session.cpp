#include "Session.h"
#include "Account.h"
#include "Language.h"
#include <iostream>

using namespace std;

Session::Session(Account* acc, long s_id) 
    : current_account(acc), withdrawal_count(0), session_id(s_id) {
}

Session::~Session() {
}

Account* Session::getAccount() {
    return current_account;
}

void Session::addTransaction(const Transaction& tx) {
    session_transactions.push_back(tx);
}

void Session::printSessionSummary(Language* lang) const {
    if (session_transactions.empty()) {
        return;
    }

    cout << "\n--- " << lang->getSessionSummaryHeader() << "(" << lang->getLabelSessionID() << ": " << session_id << ") ---" << endl;
    cout << lang->getLabelAccount() << ": " << current_account->getAccountNumber() << endl;
    for (const auto& tx : session_transactions) {
        cout << "  - " << tx.getSummaryString(lang) << endl; 
    }
    cout << "------------------------------------------\n" << endl;

}

bool Session::canWithdraw() const {
    return withdrawal_count < 3;
}

void Session::incrementWithdrawalCount() {
    withdrawal_count++;
}

int Session::getWithdrawalCount() const {
    return withdrawal_count;
}