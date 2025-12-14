#include "KoreanLanguage.h"
#include <sstream>

using namespace std;

string KoreanLanguage::getGreeting() const {
    return "환영합니다.";
}
string KoreanLanguage::getInsertCard() const {
    return "시작하려면 카드를 넣어주세요.";
}
string KoreanLanguage::getEnterPassword() const {
    return "비밀번호를 입력하세요:";
}
string KoreanLanguage::getWrongPassword() const {
    return "비밀번호가 틀렸습니다. 다시 시도해주세요.";
}
string KoreanLanguage::getInvalidCard() const {
    return "유효하지 않은 카드입니다. 이 ATM에서는 지원되지 않는 카드입니다.";
}
string KoreanLanguage::getCardBlocked() const {
    return "비밀번호를 3회 잘못 입력하셨습니다. 세션을 종료합니다.";
}
string KoreanLanguage::getMainMenu() const {
    return "거래를 선택하세요: \n1. 입금 \n2. 출금 \n3. 송금 \n4. 거래 종료";
}
string KoreanLanguage::getEndSessionPrompt() const {
    return "감사합니다. 거래를 종료합니다.";
}
string KoreanLanguage::getSessionSummaryHeader() const {
    return "거래 요약";
}
string KoreanLanguage::getTransactionSuccess() const {
    return "거래가 성공적으로 완료되었습니다.";
}
string KoreanLanguage::getDestinationAccountPrompt() const {
    return "받으실 분의 계좌번호를 입력하세요:";
}
string KoreanLanguage::getDepositMenu() const {
    return "입금 메뉴: \n1. 현금 입금 \n2. 수표 입금";
}
string KoreanLanguage::getCashCountPrompt(int denomination) const {
    stringstream ss;
    ss << denomination << " 원권 매수를 입력하세요:";
    return ss.str();
}
string KoreanLanguage::getCheckAmountPrompt() const {
    return "수표 금액을 입력하세요:";
}
string KoreanLanguage::getDepositLimitExceeded() const {
    return "오류: 1회 입금 한도(매수)를 초과했습니다.";
}
string KoreanLanguage::getWithdrawAmountPrompt() const {
    return "출금하실 금액을 입력하세요:";
}
string KoreanLanguage::getInsufficientFunds() const {
    return "오류: 계좌의 잔액이 부족합니다.";
}
string KoreanLanguage::getInsufficientATMChash() const {
    return "오류: 기기 내 현금이 부족합니다.";
}
string KoreanLanguage::getWithdrawAmountLimitExceeded() const {
    return "오류: 1회 출금 한도를 초과했습니다.";
}
string KoreanLanguage::getSessionWithdrawalLimitExceeded() const {
    return "오류: 이번 세션의 출금 횟수 한도(3회)를 초과했습니다.";
}
string KoreanLanguage::getTransferMenu() const {
    return "송금 메뉴: \n1. 현금 송금 \n2. 계좌 이체";
}
string KoreanLanguage::getTransferAmountPrompt() const {
    return "송금하실 금액을 입력하세요:";
}
string KoreanLanguage::getAdminMenu() const {
    return "관리자 메뉴: \n1. 전체 거래 내역 출력 \n2. 종료 \n선택 (1-2): ";
}
string KoreanLanguage::getSnapshotHeaderATM() const {
    return "--- ATM 현금 현황 ---";
}
string KoreanLanguage::getSnapshotHeaderAccount() const {
    return "--- 계좌 잔액 현황 ---";
}
string KoreanLanguage::getFeePrompt(long fee) const {
    stringstream ss;
    ss << "수수료 " << fee << " 원이 부과됩니다. 수수료와 입금하실 현금을 함께 투입하십시오.";
    return ss.str();
}
string KoreanLanguage::getDepositFeePrompt(long fee) const {
    stringstream ss;
    ss << "수수료" << fee << " 원이 부과됩니다.";
    return ss.str();
}
string KoreanLanguage::getFeeCashPrompt() const {
    return "수수료를 현금으로 투입해 주십시오.";
}
string KoreanLanguage::getSelectionPrompt() const {
    return "선택: ";
}
string KoreanLanguage::getInvalidSelection() const {
    return "잘못된 선택입니다. 다시 시도해주세요.";
}
string KoreanLanguage::getInvalidLanguageChoice() const {
    return "Invalid choice. / 유효하지 않은 선택입니다.";
}
string KoreanLanguage::getTransactionCancelled() const {
    return "거래가 취소되었습니다.";
}
string KoreanLanguage::getInvalidAmount() const {
    return "유효하지 않은 금액입니다.";
}
string KoreanLanguage::getDestAccountNotFound() const {
    return "입금할 계좌를 찾을 수 없습니다.";
}
string KoreanLanguage::getInsufficientFee() const {
    return "지불한 수수료가 부족합니다. 거래가 취소되었습니다.";
}
string KoreanLanguage::getReturningChange(long change) const {
    stringstream ss;
    ss << "수수료 잔돈 " << change << " 원을 반환합니다.";
    return ss.str();
}
string KoreanLanguage::getDispenseChangeError() const {
    return "오류: 잔돈을 반환할 수 없습니다.";
}
string KoreanLanguage::getCheckCountPrompt(int limit) const {
    stringstream ss;
    ss << "수표 매수를 입력하세요 (최대 " << limit << "장): ";
    return ss.str();
}
string KoreanLanguage::getCheckAmountPromptIndexed(int index) const {
    stringstream ss;
    ss << index << "번째 수표의 금액을 입력하세요: ";
    return ss.str();
}
string KoreanLanguage::getInvalidCheckAmount() const {
    return "유효하지 않은 수표 금액입니다 (최소 100,000원). 다시 입력하세요.";
}
string KoreanLanguage::getCheckTotalAmount(long total_amount) const {
    stringstream ss;
    ss << "총 입금(수표) 금액: " << total_amount << " 원";
    return ss.str();
}
string KoreanLanguage::getDispensingCashHeader() const {
    return "--- 현금을 반환합니다 ---";
}
string KoreanLanguage::getDispensingCashLine(int denom, int count) const {
    stringstream ss;
    ss << "  " << denom << " 원 x " << count;
    return ss.str();
}
string KoreanLanguage::getCashTransferHeader() const {
    return "--- 현금 송금 ---";
}
string KoreanLanguage::getAccountTransferHeader() const {
    return "--- 계좌 이체 ---";
}
string KoreanLanguage::getTransferAmountError() const {
    return "수수료 제외 후 송금액이 0원 이하입니다. 취소되었습니다.";
}
string KoreanLanguage::getAdminModeHeader() const {
    return "\n--- 관리자 모드 ---";
}
string KoreanLanguage::getHistoryHeader() const {
    return "\n--- 전체 거래 내역 ---";
}
string KoreanLanguage::getHistorySaved(string filename) const {
    stringstream ss;
    ss << "거래 내역이 " << filename << " 파일로 저장되었습니다.";
    return ss.str();
}
string KoreanLanguage::getCardNumberPrompt() const {
    return "카드 번호: ";
}
string KoreanLanguage::getWelcomeUser(string user_name) const {
    return user_name + "님, 환영합니다!";
}
string KoreanLanguage::getFeeInform(long fee) const {
    if (fee == 0) {
        return "거래 수수료가 부과되지 않습니다.";
    }
    stringstream ss;
    ss << "거래 수수료 " << fee << " 원이 계좌에서 차감됩니다.";
    return ss.str();
}
ConfirmationResponse KoreanLanguage::checkConfirmation(const string& input) const {
    if (input == "네") {
        return ConfirmationResponse::YES;
    }
    if (input == "아니오") {
        return ConfirmationResponse::NO;
    }
    return ConfirmationResponse::INVALID;
}
string KoreanLanguage::getConfirmationPrompt() const {
    return "계속하시겠습니까? (네/아니오): ";
}
string KoreanLanguage::getSummaryDeposit(long amount, const string& dest_acc, long fee) const {
    stringstream ss;
    ss << amount << "원이 " << dest_acc << "(으)로 입금됨 (수수료: " << fee << "원)";
    return ss.str();
}
string KoreanLanguage::getSummaryWithdrawal(long amount, const string& src_acc, long fee) const {
    stringstream ss;
    ss << amount << "원이 " << src_acc << "에서 출금됨 (수수료: " << fee << "원)";
    return ss.str();
}
string KoreanLanguage::getSummaryTransfer(long amount, const string& src_acc, const string& dest_acc, long fee) const {
    stringstream ss;
    ss << amount << "원이 " << src_acc << "에서 " << dest_acc << "(으)로 이체됨 (수수료: " << fee << "원)";
    return ss.str();
}
string KoreanLanguage::getLabelAccount() const {
    return "계좌";
}
string KoreanLanguage::getLabelSessionID() const {
    return "세션 번호";
}
string KoreanLanguage::getLabelTransactionID() const {
    return "거래 번호";
}
string KoreanLanguage::getAmountOutOfRange() const {
    return "입력한 숫자가 너무 큽니다. 유효한 범위 내의 숫자를 입력하세요.";
}

string KoreanLanguage::getReturnFeeCash(long amount) {
    return "투입된 수수료를 반환합니다: " + to_string(amount) + "원";
}  

string KoreanLanguage::getReturnDepositCash(long amount) {
    return "투입된 입금액을 반환합니다: " + to_string(amount) + "원";
}   

string KoreanLanguage::getCriticalDispenseError() {
    return "치명적 오류: 현금 반환에 실패했습니다.";
}