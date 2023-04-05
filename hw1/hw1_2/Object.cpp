#include "Object.h"
#include <sstream>

// Weapon begin
Weapon::Weapon()
{
    name.clear();
    reset();
}

Weapon::Weapon(string name, int ATK, int MAG, int DEF, int MDEF, int USE)
{
    this->name = name;
    this->ATK = ATK;
    this->MAG = MAG;
    this->DEF = DEF;
    this->MDEF = MDEF;
    this->USE = USE;
}

Weapon::Weapon(const Weapon &w)
{
    name = w.name;
    ATK = w.ATK;
    MAG = w.MAG;
    DEF = w.DEF;
    MDEF = w.MDEF;
    USE = w.USE;
}

// Input single line of string to initialize weapon object
Weapon::Weapon(string line)
{
    /*
     *The output format of a Weapon object:
     *Name, ATK, MAG, DEF, MDEF, USE
     *(separated with whitespace)
     */
    istringstream iss(line);
    iss >> name >> ATK >> MAG >> DEF >> MDEF >> USE;
}

// Reset the value of weapon, set all value to 0
void Weapon::reset()
{
    ATK = MAG = DEF = MDEF = 0;
}

// Decrease the usage of weapon
void Weapon::operator--(int)
{
    // If the weapon is broken, its USE will always be 0
    USE -= USE > 0 ? 1 : 0;
}

int Weapon::getATK() const
{
    return USE > 0 ? ATK : 0;
}

int Weapon::getMAG() const
{
    return USE > 0 ? MAG : 0;
}

int Weapon::getDEF() const
{
    return USE > 0 ? DEF : 0;
}

int Weapon::getMDEF() const
{
    return USE > 0 ? MDEF : 0;
}

int Weapon::getUSE() const
{
    return USE;
}

ostream &operator<<(ostream &out, const Weapon &w)
{
    out << w.name << " " << w.ATK << " " << w.MAG << " " << w.DEF << " " << w.MDEF << " " << w.USE;
    return out;
}

ofstream &operator<<(ofstream &ofs, const Weapon &w) // for debug
{
    static_cast<ostream &>(ofs) << w.name << " " << w.ATK << " " << w.MAG << " " << w.DEF << " " << w.MDEF << " " << w.USE;
    return ofs;
}
// Weapon end

// Character begin
int Char::totalATK() const
{
    return ATK + weapon.getATK();
}
int Char::totalMAG() const
{
    return MAG + weapon.getDEF();
}
int Char::totalDEF() const
{
    return DEF + weapon.getDEF();
}
int Char::totalMDEF() const
{
    return MDEF + weapon.getMDEF();
}

Char::Char()
{
    name.clear();
    HP = ATK = MAG = DEF = MDEF = POW = POW_cnt = 0;
}

Char::Char(string name, int HP, int ATK, int MAG, int DEF, int MDEF, int POW)
{
    this->name = name;
    this->HP = HP;
    this->ATK = ATK;
    this->MAG = MAG;
    this->DEF = DEF;
    this->MDEF = MDEF;
    this->POW = POW;
    this->POW_cnt = 0;
}
Char::Char(const Char &ch)
{
    name = ch.name;
    HP = ch.HP;
    ATK = ch.ATK;
    MAG = ch.MAG;
    DEF = ch.DEF;
    MDEF = ch.MDEF;
    POW = ch.POW;
    POW_cnt = ch.POW_cnt;
}

// Input single line of string to initialize Char object
Char::Char(string line)
{
    /*
     *The output format of a Char object:
     *Name, HP, ATK, MAG, DEF, MDEF, POW, POW_cnt
     *(separated with whitespace)
     */
    istringstream iss(line);
    iss >> name >> HP >> ATK >> MAG >> DEF >> MDEF >> POW;
    POW_cnt = 0;
}
// Equip weapon to character and return a new object
Char Char::operator+(const Weapon &w)
{
    Char ch(*this);
    ch.weapon = w;
    return ch;
}

// Increase the POW_cnt by 1
void Char::operator++(int)
{
    POW_cnt++;
}
// Battle
void Char::operator-(Char &defender)
{
    Char &attacker = *this;

    if (attacker.POW_cnt == attacker.POW)
    {
        // launches a magical attack
        defender.HP -= attacker.totalMAG() - defender.totalMDEF();
        if (defender.HP < 0)
            defender.HP = 0;

        attacker.POW_cnt = 0; // reset attacker.POW_cnt
    }
    else
    {
        // launches a physical attack
        defender.HP -= attacker.totalATK() - defender.totalDEF();
        if (defender.HP < 0)
            defender.HP = 0;

        attacker.weapon--;  // weapon.USE will decrease by 1 after each physical attack
        attacker.POW_cnt++; // increase attacker.POW_cnt
    }

    if (defender.HP > 0) // Counterattack if defender is alive
        defender - attacker;
}

ostream &operator<<(ostream &out, const Char &ch)
{
    out << ch.name << " " << ch.HP << " " << ch.ATK << " " << ch.MAG << " " << ch.DEF << " " << ch.MDEF << " " << ch.POW << " " << ch.POW_cnt;
    if (ch.weapon.getUSE() > 0)
        out << endl
            << ch.weapon;
    return out;
}

ofstream &operator<<(ofstream &ofs, const Char &ch) // for debug
{
    static_cast<ostream &>(ofs) << ch.name << " " << ch.HP << " " << ch.ATK << " " << ch.MAG << " " << ch.DEF << " " << ch.MDEF << " " << ch.POW << " " << ch.POW_cnt;
    if (ch.weapon.getUSE() > 0)
        static_cast<ostream &>(ofs) << endl
                                    << ch.weapon;
    return ofs;
}
// Character end