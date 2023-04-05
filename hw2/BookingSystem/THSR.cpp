#include "THSR.h"

THSR::THSR()
{
}

THSR::THSR(int _train_no, int _drive, string _date, string _travel, string _from, string _to, string _Class, int _car, string _seat)
    : train_information(_train_no, _drive, _date, _travel, _from, _to)
{
    Class = _Class;
    car = _car;
    seat = _seat;
}

void THSR::print_information()
{
    train_information::print_information();

    cout << "        Class: " << Class << endl;
    cout << "        Car, seat: " << car << ", " << seat << endl;
}

/*bool THSR::operator<(const THSR &t)
{
    return (train_information &)(*this) < (train_information &)(t);
}*/