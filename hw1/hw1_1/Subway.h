// Subway.h
#ifndef _SUBWAY_H_
#define _SUBWAY_H_
#include <string>
#include <iostream>
using namespace std;

class Subway
{
private:
    string bread;
    string extra;
    string combo;
    void printErrorMsg();
    void checkInputNumber(int &n);

public:
    Subway();
    int getInputBread();
    int getInputCombo();
    void getInputExtra(int inputExtra[]);
    void setBread(int inputBread);
    void setExtra(int inputExtra[]);
    void setCombo(int inputCombo);
    void outputDescription();
    double computePrice(int numberofExtra, int inputCombo);
};

#endif
