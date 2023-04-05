#ifndef _OBJECT_H__
#define _OBJECT_H__

#include <string>
#include <iostream>
#include <fstream> // for debug
using namespace std;

class Weapon
{
private:
    string name;
    int ATK;
    int MAG;
    int DEF;
    int MDEF;
    int USE;

public:
    Weapon();
    Weapon(string name, int ATK, int MAG, int DEF, int MDEF, int USE);
    Weapon(const Weapon &);
    // Input single line of string to initialize weapon object
    Weapon(string);
    // Reset the value of weapon, set all value to 0
    void reset();
    // Decrease the usage of weapon
    void operator--(int);
    int getATK() const;
    int getMAG() const;
    int getDEF() const;
    int getMDEF() const;
    int getUSE() const;
    friend ostream &operator<<(ostream &, const Weapon &);
    friend ofstream &operator<<(ofstream &, const Weapon &); // for debug
};
class Char
{
private:
    string name;
    int HP;      // Health
    int ATK;     // Attack
    int MAG;     // Magic
    int DEF;     // Defense
    int MDEF;    // Magical Defense
    int POW;     // Amount of power to use magic attack
    int POW_cnt; // Power storage
    Weapon weapon;

    int totalATK() const;
    int totalMAG() const;
    int totalDEF() const;
    int totalMDEF() const;

public:
    Char();
    Char(string name, int HP, int ATK, int MAG, int DEF, int MDEF, int POW);
    Char(const Char &);
    // Input single line of string to initialize Char object
    Char(string);
    // Equip weapon to character and return a new object
    Char operator+(const Weapon &);
    // Increase the POW_cnt by 1
    void operator++(int);
    // Battle
    void operator-(Char &);
    friend ostream &operator<<(ostream &, const Char &);
    friend ofstream &operator<<(ofstream &, const Char &); // for debug
};

#endif