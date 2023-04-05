#include "train_information.h"
// #include <cstring>

train_information::train_information()
{
}

train_information::train_information(int _train_no, int _drive, string _date, string _travel, string _from, string _to)
{
    train_no = _train_no;
    drive = _drive;
    date = _date;
    travel = _travel;
    from = _from;
    to = _to;
}

void train_information::print_information()
{
    cout << "        Date: " << date << endl;
    cout << "        Train no: " << train_no << endl;
    cout << "        From " << from << " to " << to << endl;
    cout << "        Driving time(mins): " << drive << endl;
    cout << "        Travel: " << travel << endl;
}
