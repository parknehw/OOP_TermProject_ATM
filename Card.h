#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

enum class CardType {
    DEBIT_CARD, 
    ADMIN_CARD  
};

class Card {
protected:
    string card_number;
    string password;

public:
    Card(string c_num, string pw);

    virtual ~Card() = default;

    virtual bool validatePassword(string pw) = 0;

    virtual CardType getType() const = 0;

    string getCardNumber() const;
};

#endif