#ifndef DEBITCARD_H
#define DEBITCARD_H

#include "Card.h" 

using namespace std;

class Account;

class DebitCard : public Card {
private:
    Account* linkedAccount; 

public:
    DebitCard(string c_num, string pw, Account* acc);

    bool validatePassword(string pw) override;
    CardType getType() const override;

    Account* getAccount();
};

#endif