#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

using namespace std;

enum class ConfirmationResponse {
    YES,
    NO,
    INVALID
};

class Language {
public:
    virtual ~Language() = default; 
    virtual string getGreeting() const = 0; 
    virtual string getInsertCard() const = 0;
    virtual string getEnterPassword() const = 0;
    virtual string getWrongPassword() const = 0;
    virtual string getInvalidCard() const = 0;
    virtual string getCardBlocked() const = 0;
    virtual string getMainMenu() const = 0;
    virtual string getEndSessionPrompt() const = 0;
    virtual string getSessionSummaryHeader() const = 0;
    virtual string getSelectionPrompt() const = 0;
    virtual string getInvalidSelection() const = 0;
    virtual string getInvalidLanguageChoice() const = 0;
    virtual string getTransactionCancelled() const = 0;
    virtual string getInvalidAmount() const = 0;
    virtual string getConfirmationPrompt() const = 0;
    virtual string getTransactionSuccess() const = 0;
    virtual string getFeePrompt(long fee) const = 0;
    virtual string getDestinationAccountPrompt() const = 0;
    virtual string getDestAccountNotFound() const = 0;
    virtual string getInsufficientFee() const = 0;
    virtual string getReturningChange(long change) const = 0;
    virtual string getDispenseChangeError() const = 0;
    virtual string getDepositMenu() const = 0;
    virtual string getCashCountPrompt(int denomination) const = 0;
    virtual string getCheckAmountPrompt() const = 0;
    virtual string getDepositLimitExceeded() const = 0;
    virtual string getCheckCountPrompt(int limit) const = 0;
    virtual string getCheckAmountPromptIndexed(int index) const = 0;
    virtual string getInvalidCheckAmount() const = 0;
    virtual string getCheckTotalAmount(long total_amount) const = 0;
    virtual string getFeeCashPrompt() const = 0;
    virtual string getWithdrawAmountPrompt() const = 0;
    virtual string getInsufficientFunds() const = 0;
    virtual string getInsufficientATMChash() const = 0;
    virtual string getWithdrawAmountLimitExceeded() const = 0;
    virtual string getSessionWithdrawalLimitExceeded() const = 0;
    virtual string getDispensingCashHeader() const = 0;
    virtual string getDispensingCashLine(int denom, int count) const = 0;
    virtual string getFeeInform(long fee) const = 0;
    virtual string getTransferMenu() const = 0;
    virtual string getTransferAmountPrompt() const = 0;
    virtual string getCashTransferHeader() const = 0;
    virtual string getAccountTransferHeader() const = 0;
    virtual string getTransferAmountError() const = 0;
    virtual string getAdminModeHeader() const = 0;
    virtual string getHistoryHeader() const = 0;
    virtual string getHistorySaved(string filename) const = 0;
    virtual string getAdminMenu() const = 0;
    virtual string getSnapshotHeaderATM() const = 0;
    virtual string getSnapshotHeaderAccount() const = 0;
    virtual string getCardNumberPrompt() const = 0;
    virtual string getWelcomeUser(string user_name) const = 0;
    virtual ConfirmationResponse checkConfirmation(const string& input) const = 0;
    virtual string getSummaryDeposit(long amount, const string& dest_acc, long fee) const = 0;
    virtual string getSummaryWithdrawal(long amount, const string& src_acc, long fee) const = 0;
    virtual string getSummaryTransfer(long amount, const string& src_acc, const string& dest_acc, long fee) const = 0;
    virtual string getLabelAccount() const = 0;
    virtual string getLabelSessionID() const = 0;
    virtual string getLabelTransactionID() const = 0;
    virtual string getAmountOutOfRange() const = 0;
    virtual string getDepositFeePrompt(long fee) const = 0;
    virtual string getReturnFeeCash(long amount) = 0;
    virtual string getReturnDepositCash(long amount) = 0;
    virtual string getCriticalDispenseError() = 0;
};

#endif