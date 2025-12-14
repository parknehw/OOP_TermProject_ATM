#ifndef ENGLISHLANGUAGE_H
#define ENGLISHLANGUAGE_H

#include "Language.h"

using namespace std;

class EnglishLanguage : public Language {
public:
    string getGreeting() const override;
    string getInsertCard() const override;
    string getEnterPassword() const override;
    string getWrongPassword() const override;
    string getInvalidCard() const override;
    string getCardBlocked() const override;
    string getMainMenu() const override;
    string getEndSessionPrompt() const override;
    string getSessionSummaryHeader() const override;
    string getTransactionSuccess() const override;
    string getFeePrompt(long fee) const override;
    string getDestinationAccountPrompt() const override;
    string getDepositMenu() const override;
    string getCashCountPrompt(int denomination) const override;
    string getCheckAmountPrompt() const override;
    string getDepositLimitExceeded() const override;
    string getWithdrawAmountPrompt() const override;
    string getInsufficientFunds() const override;
    string getInsufficientATMChash() const override;
    string getWithdrawAmountLimitExceeded() const override;
    string getSessionWithdrawalLimitExceeded() const override;
    string getTransferMenu() const override;
    string getTransferAmountPrompt() const override;
    string getAdminMenu() const override;
    string getSnapshotHeaderATM() const override;
    string getSnapshotHeaderAccount() const override;
    string getSelectionPrompt() const override;
    string getInvalidSelection() const override;
    string getInvalidLanguageChoice() const override;
    string getTransactionCancelled() const override;
    string getInvalidAmount() const override;
    string getDestAccountNotFound() const override;
    string getInsufficientFee() const override;
    string getReturningChange(long change) const override;
    string getDispenseChangeError() const override;
    string getCheckCountPrompt(int limit) const override;
    string getCheckAmountPromptIndexed(int index) const override;
    string getInvalidCheckAmount() const override;
    string getCheckTotalAmount(long total_amount) const override;
    string getDispensingCashHeader() const override;
    string getDispensingCashLine(int denom, int count) const override;
    string getCashTransferHeader() const override;
    string getAccountTransferHeader() const override;
    string getTransferAmountError() const override;
    string getAdminModeHeader() const override;
    string getHistoryHeader() const override;
    string getHistorySaved(string filename) const override;
    string getCardNumberPrompt() const override;
    string getWelcomeUser(string user_name) const override;
    string getFeeInform(long fee) const override;
    string getConfirmationPrompt() const override;
    ConfirmationResponse checkConfirmation(const string& input) const override;
    string getFeeCashPrompt() const override;
    string getSummaryDeposit(long amount, const string& dest_acc, long fee) const override;
    string getSummaryWithdrawal(long amount, const string& src_acc, long fee) const override;
    string getSummaryTransfer(long amount, const string& src_acc, const string& dest_acc, long fee) const override;
    string getLabelAccount() const override;
    string getLabelSessionID() const override;
    string getLabelTransactionID() const override;
    string getAmountOutOfRange() const override;
    string getDepositFeePrompt(long fee) const override;
    string getReturnFeeCash(long amount) override;
    string getReturnDepositCash(long amount) override;
    string getCriticalDispenseError() override;
};

#endif