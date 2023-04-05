#include <fstream>
#include <vector>
#include "Object.h"

int main(int argc, char **argv)
{
    
    argv[1] = (char *)"character.in"; // for debug
    argv[2] = (char *)"weapon.in";    // for debug
    ofstream ofs("debug.txt");        // for debug
    
    string line;
    vector<Char> chars;
    vector<Weapon> weapons;
    Char *c;
    Weapon *w;
    ifstream fin(argv[1]);
    while (getline(fin, line))
    {
        // Constructor with input string (single row)
        c = new Char(line);
        chars.push_back((*c));
    }
    fin.close();
    fin.open(argv[2]);
    while (getline(fin, line))
    {
        // Constructor with input string (single row)
        w = new Weapon(line);
        weapons.push_back((*w));
    }
    fin.close();
    /*
    Q1 (20%)
    1. Complete constructors
    2. Complete operator overloading of <<
    */
    cout << "[Problem1]" << endl;

    for (int i = 0; i < chars.size(); i++)
        cout << chars[i] << endl;
    for (int i = 0; i < weapons.size(); i++)
        cout << weapons[i] << endl;
    /*
    Q2 (20%)
    1. Equip the character with weapon with operator +
    */
    cout << "[Problem2]" << endl;

    Char t1 = chars[0] + weapons[0];
    cout << chars[0] << endl;
    cout << weapons[0] << endl;
    ;
    cout << t1 << endl;
    Char t2 = chars[1] + weapons[1];
    cout << chars[1] << endl;
    cout << weapons[1] << endl;
    ;
    cout << t2 << endl;
    /*
    Q3 (30%)
    1. Charge power of character with operator ++
    2. Decrease the usage of weapon with operator --
    */
    cout << "[Problem3]" << endl;
    t1++;
    cout << t1 << endl;
    Weapon w1(weapons[0]);
    w1--;
    cout << w1 << endl;
    /*
    Q4 (30%)
    1. Battle operation with operator -
    */
    cout << "[Problem4]" << endl;
    t1 - t2;
    cout << t1 << endl;
    cout << t2 << endl;
    return 0;
}
