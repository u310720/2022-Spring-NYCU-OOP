#ifndef _TRANSACTION
#define _TRANSACTION

#include <iostream>
#include <string>

using namespace std;

struct Transaction
{
    string id;
    double fee;
    string buyer;
    string seller;
    double coinAmount;
    double usDollar;
    
    Transaction() {}
    Transaction(string &_id, double _fee, string &_buyer, string &_seller, double _coinAmount, double _usDollar)
    {
        id = _id;
        fee = _fee;
        buyer = _buyer;
        seller = _seller;
        coinAmount = _coinAmount;
        usDollar = _usDollar;
    }
};



#endif
