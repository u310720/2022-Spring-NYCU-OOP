// hw1-1.cpp
#include <iostream>
#include "Subway.h"
using namespace std;

int main()
{
    while (true)
    {
        int inputBread, inputCombo, inputExtra[10] = {0};
        Subway yourSubway;
        inputBread = yourSubway.getInputBread();
        inputCombo = yourSubway.getInputCombo();
        yourSubway.getInputExtra(inputExtra);
        yourSubway.setBread(inputBread);
        yourSubway.setCombo(inputCombo);
        yourSubway.setExtra(inputExtra);
        yourSubway.outputDescription();

        int numberofExtra = 0, i = 0;
        while (inputExtra[i] != 0)
        {
            numberofExtra++;
            i++;
        }
        double price = yourSubway.computePrice(numberofExtra, inputCombo);
        cout << endl
             << "Your subway's price: $" << price << endl
             << "Thank you for your coming!\n"
             << endl;
    }
    return 0;
}
