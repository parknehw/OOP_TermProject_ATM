#ifndef ADMINCARD_H
#define ADMINCARD_H

#include "Card.h"
using namespace std;

class Bank;

class AdminCard : public Card {

private:
    Bank* managing_bank;

public:
    AdminCard(string c_num, string pw, Bank* bank);

    bool validatePassword(string pw) override;
    CardType getType() const override;

    Bank* getManagingBank() const;
};

#endif