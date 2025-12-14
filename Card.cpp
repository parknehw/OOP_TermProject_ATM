#include "Card.h"

using namespace std;

Card::Card(string c_num, string pw) {
    this->card_number = c_num;
    this->password = pw;
}

string Card::getCardNumber() const {
    return card_number;
}