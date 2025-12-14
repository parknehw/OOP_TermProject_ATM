#include "AdminCard.h"
#include "Bank.h"

using namespace std;

AdminCard::AdminCard(string c_num, string pw, Bank* bank)
    : Card(c_num, pw), managing_bank(bank) {
}

bool AdminCard::validatePassword(string pw) {
    return this->password == pw;
}

CardType AdminCard::getType() const {
    return CardType::ADMIN_CARD;
}

Bank* AdminCard::getManagingBank() const {
    return managing_bank;
}