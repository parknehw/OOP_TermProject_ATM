#include "DebitCard.h"
#include "Account.h"

using namespace std;

DebitCard::DebitCard(string c_num, string pw, Account* acc)
    : Card(c_num, pw) {
    this->linkedAccount = acc;
}

bool DebitCard::validatePassword(string pw) {
    return this->password == pw;
}

CardType DebitCard::getType() const {
    return CardType::DEBIT_CARD; 
}

Account* DebitCard::getAccount() {
    return linkedAccount;
}