#include "Subway.h"

#include <limits>
using std::numeric_limits;

void Subway::checkInputNumber(int &n)
{
    cin >> n;
    if (cin.fail())
    {
        cin.clear();
        // cin.sync(); // it does not work on linux workstation(NYCU OOP), but windows can
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        n = -2; // set to error state 2 because n will be 0 when cin.fail occurs, and n == 0 will cause some exceptions
    }
    if (n == -1) // shutdown instruction
        exit(0);
}

void Subway::printErrorMsg()
{
    cout << "Invalid input. Please input again:" << endl;
}

Subway::Subway()
{
}

int Subway::getInputBread()
{
    int bread = -1;
    cout << "Choose bread\'s type:" << endl
         << "1. Honey Oat" << endl
         << "2. Parmesan Oregano" << endl
         << "3. Wheat" << endl;
    checkInputNumber(bread);
    cout << endl;
    while (bread < 1 || bread > 3)
    {
        printErrorMsg();
        checkInputNumber(bread);
        cout << endl;
    }
    return bread;
}

int Subway::getInputCombo()
{
    int combo;
    cout << "Choose Combo:" << endl
         << "1. Combo A" << endl
         << "2. Combo B" << endl
         << "3. Combo C" << endl;
    checkInputNumber(combo);
    cout << endl;
    while (combo < 1 || combo > 3)
    {
        printErrorMsg();
        checkInputNumber(combo);
        cout << endl;
    }
    return combo;
}

void Subway::getInputExtra(int inputExtra[])
{
    // There will be no repeated extras selected in the testcase
    int idx = 0, ingredient = -1;
    bool ingredientSelected[7] = {false};
    do
    {
        cout << "Choose extras:" << endl
             << "1. Avocado" << endl
             << "2. Bacon" << endl
             << "3. Egg Patty" << endl
             << "4. Extra Cheese" << endl
             << "5. Double Meat" << endl
             << "6. Egg Mayo" << endl;

        checkInputNumber(ingredient);
        cout << endl;
        while (ingredient < 1 || ingredient > 6 || ingredientSelected[ingredient])
        {
            if (ingredient == 0)
                break;

            printErrorMsg();
            checkInputNumber(ingredient);
            cout << endl;
        }
        ingredientSelected[ingredient] = true;
    } while (ingredient != 0);

    for (int idx = 0, ingredient = 1; ingredient < 7; ingredient++)
        if (ingredientSelected[ingredient])
            inputExtra[idx++] = ingredient;
}

void Subway::setBread(int inputBread)
{
    switch (inputBread)
    {
    case 1:
        bread = "Honey Oat";
        break;
    case 2:
        bread = "Parmesan Oregano";
        break;
    case 3:
        bread = "Wheat";
        break;
    }
}

void Subway::setExtra(int inputExtra[])
{
    for (int idx = 0; inputExtra[idx] != 0 && idx < 10; idx++)
    {
        switch (inputExtra[idx])
        {
        case 1:
            extra.append("Avocado & ");
            break;
        case 2:
            extra.append("Bacon & ");
            break;
        case 3:
            extra.append("Egg Patty & ");
            break;
        case 4:
            extra.append("Extra Cheese & ");
            break;
        case 5:
            extra.append("Double Meat & ");
            break;
        case 6:
            extra.append("Egg Mayo & ");
            break;
        }
    }
    if (inputExtra[0] == 0)
        extra = "None";
    else
        extra.erase(extra.end() - 3, extra.end()); // erase " & "
}

void Subway::setCombo(int inputCombo)
{
    switch (inputCombo)
    {
    case 1:
        combo = "Combo A";
        break;
    case 2:
        combo = "Combo B";
        break;
    case 3:
        combo = "Combo C";
        break;
    }
}

void Subway::outputDescription()
{
    cout << "Your order:" << endl
         << "Bread: " << bread << endl
         << "Combo: " << combo << endl
         << "Extras: " << extra << endl;
}

double Subway::computePrice(int numberofExtra, int inputCombo)
{
    double price = 15 + numberofExtra * 2;
    switch (inputCombo)
    {
    case 1:
        price += 3;
        break;
    case 2:
        price += 5;
        break;
    case 3:
        price += 7;
        break;
    }
    return price;
}
