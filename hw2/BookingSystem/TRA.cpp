#include "TRA.h"

TRA::TRA()
{
}

TRA::TRA(int _train_no, int _drive, string _date, string _travel, string _from, string _to, string _train_type, int _car, string _seat)
    : train_information(_train_no, _drive, _date, _travel, _from, _to)
{
    train_type = _train_type;
    car = _car;
    seat = _seat;
}

void TRA::print_information()
{
    train_information::print_information();
    cout << "        Train type: " << train_type << endl;
    cout << "        Car, Seat: " << car << ", " << seat << endl;
}

/*bool TRA::operator<(const TRA &t)
{
    return (train_information &)(*this) < (train_information &)(t);
}*/
