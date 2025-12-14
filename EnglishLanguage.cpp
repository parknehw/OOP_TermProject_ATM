#include "EnglishLanguage.h"
#include <sstream>

using namespace std;

string EnglishLanguage::getGreeting() const {
    return "Welcome.";
}
string EnglishLanguage::getInsertCard() const {
    return "To start, please insert your debit card.";
}
string EnglishLanguage::getEnterPassword() const {
    return "Enter Password:";
}
string EnglishLanguage::getWrongPassword() const {
    return "Wrong Password. Please try again.";
}
string EnglishLanguage::getInvalidCard() const {
    return "Invalid Card. This card is not supported by this ATM.";
}
string EnglishLanguage::getCardBlocked() const {
    return "You have entered the wrong password 3 times. The session is aborted.";
}
string EnglishLanguage::getMainMenu() const {
    return "Select transaction: \n1. Deposit \n2. Withdrawal \n3. Transfer \n4. End Session";
}
string EnglishLanguage::getEndSessionPrompt() const {
    return "Thank you. Ending session.";
}
string EnglishLanguage::getSessionSummaryHeader() const {
    return "Session Summary";
}
string EnglishLanguage::getTransactionSuccess() const {
    return "Transaction successful.";
}
string EnglishLanguage::getDestinationAccountPrompt() const {
    return "Enter destination account number:";
}
string EnglishLanguage::getDepositMenu() const {
    return "Deposit Menu: \n1. Cash \n2. Check";
}
string EnglishLanguage::getCashCountPrompt(int denomination) const {
    stringstream ss;
    ss << "Enter count for " << denomination << " KRW bills:";
    return ss.str();
}
string EnglishLanguage::getCheckAmountPrompt() const {
    return "Enter check amount:";
}
string EnglishLanguage::getDepositLimitExceeded() const {
    return "Error: Deposit limit exceeded.";
}
string EnglishLanguage::getWithdrawAmountPrompt() const {
    return "Enter amount to withdraw:";
}
string EnglishLanguage::getInsufficientFunds() const {
    return "Error: Insufficient funds in account.";
}
string EnglishLanguage::getInsufficientATMChash() const {
    return "Error: Insufficient cash in ATM.";
}
string EnglishLanguage::getWithdrawAmountLimitExceeded() const {
    return "Error: Withdrawal amount limit exceeded.";
}
string EnglishLanguage::getSessionWithdrawalLimitExceeded() const {
    return "Error: Session withdrawal limit exceeded.";
}
string EnglishLanguage::getTransferMenu() const {
    return "Transfer Menu: \n1. Cash Transfer \n2. Account Transfer";
}
string EnglishLanguage::getTransferAmountPrompt() const {
    return "Enter amount to transfer:";
}
string EnglishLanguage::getAdminMenu() const {
    return "Admin Menu: \n1. Print Transaction History \n2. Exit \nSelect (1-2): ";
}
string EnglishLanguage::getSnapshotHeaderATM() const {
    return "--- ATM Status ---";
}
string EnglishLanguage::getSnapshotHeaderAccount() const {
    return "--- Account Status ---";
}
string EnglishLanguage::getFeePrompt(long fee) const {
    stringstream ss;
    ss << "A fee of " << fee << " KRW will be charged. Insert cash and transaction fee.";
    return ss.str();
}
string EnglishLanguage::getDepositFeePrompt(long fee) const {
    stringstream ss;
    ss << "A fee of " << fee << " KRW will be charged.";
    return ss.str();
}
string EnglishLanguage::getFeeCashPrompt() const {
    return "Please insert additional cash for the fee.";
}
string EnglishLanguage::getSelectionPrompt() const {
    return "Select: ";
}
string EnglishLanguage::getInvalidSelection() const {
    return "Invalid selection. Try again.";
}
string EnglishLanguage::getInvalidLanguageChoice() const {
    return "Invalid choice. / 유효하지 않은 선택입니다.";
}
string EnglishLanguage::getTransactionCancelled() const {
    return "Transaction has been cancelled.";
}
string EnglishLanguage::getInvalidAmount() const {
    return "Invalid amount.";
}
string EnglishLanguage::getDestAccountNotFound() const {
    return "Destination account not found.";
}
string EnglishLanguage::getInsufficientFee() const {
    return "Insufficient fee paid. Transaction cancelled.";
}
string EnglishLanguage::getReturningChange(long change) const {
    stringstream ss;
    ss << "Returning change for fee: " << change << " KRW";
    return ss.str();
}
string EnglishLanguage::getDispenseChangeError() const {
    return "Error: Could not dispense change.";
}
string EnglishLanguage::getCheckCountPrompt(int limit) const {
    stringstream ss;
    ss << "Enter number of checks (limit " << limit << "): ";
    return ss.str();
}
string EnglishLanguage::getCheckAmountPromptIndexed(int index) const {
    stringstream ss;
    ss << "Enter amount for check " << index << ": ";
    return ss.str();
}
string EnglishLanguage::getInvalidCheckAmount() const {
    return "Invalid check amount (minimum 100,000 KRW). Please re-enter.";
}
string EnglishLanguage::getCheckTotalAmount(long total_amount) const {
    stringstream ss;
    ss << "Total check deposit amount: " << total_amount << " KRW";
    return ss.str();
}
string EnglishLanguage::getDispensingCashHeader() const {
    return "--- Dispensing Cash ---";
}
string EnglishLanguage::getDispensingCashLine(int denom, int count) const {
    stringstream ss;
    ss << "  " << denom << " KRW x " << count;
    return ss.str();
}
string EnglishLanguage::getCashTransferHeader() const {
    return "--- Cash Transfer ---";
}
string EnglishLanguage::getAccountTransferHeader() const {
    return "--- Account Transfer ---";
}
string EnglishLanguage::getTransferAmountError() const {
    return "Transfer amount is 0 or less after fee. Cancelled.";
}
string EnglishLanguage::getAdminModeHeader() const {
    return "\n--- ADMIN MODE ---";
}
string EnglishLanguage::getHistoryHeader() const {
    return "\n--- Total Transaction History ---";
}
string EnglishLanguage::getHistorySaved(string filename) const {
    stringstream ss;
    ss << "History saved to " << filename;
    return ss.str();
}
string EnglishLanguage::getCardNumberPrompt() const {
    return "Card Number: ";
}
string EnglishLanguage::getWelcomeUser(string user_name) const {
    return "Welcome, " + user_name + "!";
}
string EnglishLanguage::getFeeInform(long fee) const {
    if (fee == 0) {
        return "No transaction fee will be charged.";
    }
    stringstream ss;
    ss << "A transaction fee of " << fee << " KRW will be deducted from your account.";
    return ss.str();
}
ConfirmationResponse EnglishLanguage::checkConfirmation(const string& input) const {
    if (input == "y" || input == "Y") {
        return ConfirmationResponse::YES;
    }
    if (input == "n" || input == "N") {
        return ConfirmationResponse::NO;
    }
    return ConfirmationResponse::INVALID;
}
string EnglishLanguage::getConfirmationPrompt() const {
    return "Do you want to proceed? (y/n): ";
}
string EnglishLanguage::getSummaryDeposit(long amount, const string& dest_acc, long fee) const {
    stringstream ss;
    ss << amount << "Won added to " << dest_acc << " (Fee: " << fee << "Won)";
    return ss.str();
}
string EnglishLanguage::getSummaryWithdrawal(long amount, const string& src_acc, long fee) const {
    stringstream ss;
    ss << amount << "Won withdrawed from " << src_acc << " (Fee: " << fee << "Won)";
    return ss.str();
}
string EnglishLanguage::getSummaryTransfer(long amount, const string& src_acc, const string& dest_acc, long fee) const {
    stringstream ss;
    ss << amount << "Won transfered from " << src_acc << " to " << dest_acc << " (Fee: " << fee << "Won)";
    return ss.str();
}
string EnglishLanguage::getLabelAccount() const {
    return "Account";
}
string EnglishLanguage::getLabelSessionID() const {
    return "Session ID";
}
string EnglishLanguage::getLabelTransactionID() const {
    return "Transaction ID";
}
string EnglishLanguage::getAmountOutOfRange() const {
    return "The number entered is too large. Please enter a number within the valid range.";
}

string EnglishLanguage::getReturnFeeCash(long amount) {
    return "Returning fee cash: " + to_string(amount) + " KRW";
}

string EnglishLanguage::getReturnDepositCash(long amount) {
    return "Returning deposit cash: " + to_string(amount) + " KRW";
}

string EnglishLanguage::getCriticalDispenseError() {
    return "CRITICAL ERROR: Failed to dispense cash.";
}
