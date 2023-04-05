#include "BookingSystem.h"
#include <fstream>

enum SELECT
{
    TRA_ONE_WAY,
    TRA_ROUND_TRIP,
    THSR_ONE_WAY,
    THSR_ROUND_TRIP
};

namespace BS_lambda
{
    auto replace = [](string &str, char oldChar, char newChar)
    {
        for (auto &c : str)
            if (c == oldChar)
                c = newChar;
    };
    auto stoi = [](const string &str)
    {
        int num = 0, sign = 1;
        for (const char &c : str)
        {
            if (isdigit(c))
            {
                num *= 10;
                num += (int)c - 48;
            }
            else
            {
                if (num != 0) // exception 1, "  123ABCD" -> return 123
                    break;
                else if (c == '-') // exception 2, num == 0 & c == '-', then return a negtive number
                    sign = -1;
            }
        }
        return sign * num;
    };
    auto shrink = [](string &str)
    {
        while (str.back() == ' ')
            str.pop_back();
        auto iter = str.begin();
        while (*iter == ' ')
            ++iter;
        str.erase(str.begin(), iter);
    };
    auto replace_and_shrink = [](string &str, char oldChar, char newChar)
    {
        replace(str, oldChar, newChar);
        shrink(str);
    };
};

BookingSystem::BookingSystem()
{
}

void BookingSystem::BookingSystemShell()
{
    string cmd;

    p();
    cout << "$: ";
    while (getline(cin, cmd) && cmd != "q")
    {
        if (cmd == "p")
            p();
        else if (cmd == "b")
            b();
        else if (cmd == "u")
            u();
        else if (cmd == "s")
            s();
        else
            cout << "error command!" << endl;
        cout << "$: ";
    }

    cout << endl;
    cout << "exit." << endl;
}

void BookingSystem::p()
{
    cout << "=====My tickets folder=====" << endl;
    cout << "THSR tickets num: " << THSR_m.size() << endl;
    cout << "TRA tickets num: " << TRA_m.size() << endl;
    cout << endl;

    int cnt = 0;
    if (THSR_m.size() != 0)
        cout << "THSR:" << endl;
    for (auto &thsr : THSR_m)
    {
        cout << "ticket#" << cnt++ << endl;
        thsr.second.print_information();
    }

    cnt = 0;
    if (TRA_m.size() != 0)
        cout << "TRA:" << endl;
    for (auto &tra : TRA_m)
    {
        cout << "ticket#" << cnt++ << endl;
        tra.second.print_information();
    }
}

void BookingSystem::b()
{
    string cmd, tmp, line;

    getline(cin, cmd);

    if (cmd == "TRA")
    {
        getline(cin, line);
        if (line.find("One way") != string::npos)
            parseTicket(line, TRA_ONE_WAY);
        else if (line.find("Round Trip") != string::npos)
            parseTicket(line, TRA_ROUND_TRIP);
        else
            cout << "error command!" << endl;
    }
    else if (cmd == "THSR")
    {
        getline(cin, line);
        if (line.find("One way") != string::npos)
            parseTicket(line, THSR_ONE_WAY);
        else if (line.find("Round Trip") != string::npos)
            parseTicket(line, THSR_ROUND_TRIP);
        else
            cout << "error command!" << endl;
    }
    else
        cout << "error command!" << endl;
}

void BookingSystem::s()
{
    bool printFlag = false;
    string date;
    getline(cin, date);
    if (THSR_m.find(date) != THSR_m.end())
    {
        printFlag = true;
        cout << "You have one THSR ticket: " << endl;
        THSR_m[date].print_information();
    }
    if (TRA_m.find(date) != TRA_m.end())
    {
        printFlag = true;
        cout << "You have one TRA ticket: " << endl;
        TRA_m[date].print_information();
    }
    if (!printFlag)
        cout << "You don't have any ticket whose Date is " << date << "." << endl;
}

void BookingSystem::u()
{
    string cmd, date;
    getline(cin, cmd);
    if (cmd == "TRA")
    {
        getline(cin, date);
        auto iter = TRA_m.find(date);
        if (iter != TRA_m.end())
        {
            TRA_m.erase(iter);
            cout << "Used. " << endl;
        }
        else
            cout << "You don't have TRA " << date << " ticket." << endl;
    }
    else if (cmd == "THSR")
    {
        getline(cin, date);
        auto iter = THSR_m.find(date);
        if (iter != THSR_m.end())
        {
            THSR_m.erase(iter);
            cout << "Used. " << endl;
        }
        else
            cout << "You don't have THSR " << date << " ticket." << endl;
    }
    else
        cout << "error command!" << endl;
}

void BookingSystem::parseTicket(string line, int select)
{
    BS_lambda::replace(line, ' ', '_');
    BS_lambda::replace(line, ',', ' ');

    istringstream iss(line);
    int train_no, drive, car;
    string date, travel, from, to, train_type /*or class*/, seat, tmp;

    iss >> tmp;
    train_no = BS_lambda::stoi(tmp);
    iss >> tmp;
    drive = BS_lambda::stoi(tmp);
    iss >> date >> travel >> from >> to >> train_type >> tmp >> seat;
    car = BS_lambda::stoi(tmp);

    BS_lambda::replace_and_shrink(date, '_', ' ');
    BS_lambda::replace_and_shrink(travel, '_', ' ');
    BS_lambda::replace_and_shrink(from, '_', ' ');
    BS_lambda::replace_and_shrink(to, '_', ' ');
    BS_lambda::replace_and_shrink(train_type, '_', ' ');
    BS_lambda::replace_and_shrink(seat, '_', ' ');

    switch (select)
    {
    case TRA_ONE_WAY:
        TRA_m[date] = TRA(train_no, drive, date, travel, from, to, train_type, car, seat);
        break;

    case TRA_ROUND_TRIP:
        TRA_m[date] = TRA(train_no, drive, date, travel, from, to, train_type, car, seat);
        iss >> tmp;
        train_no = BS_lambda::stoi(tmp);
        iss >> tmp;
        drive = BS_lambda::stoi(tmp);
        iss >> date >> train_type >> tmp >> seat;
        car = BS_lambda::stoi(tmp);

        BS_lambda::replace_and_shrink(date, '_', ' ');
        BS_lambda::replace_and_shrink(train_type, '_', ' ');
        BS_lambda::replace_and_shrink(seat, '_', ' ');

        TRA_m[date] = TRA(train_no, drive, date, travel, to, from, train_type, car, seat);
        break;

    case THSR_ONE_WAY:
        THSR_m[date] = THSR(train_no, drive, date, travel, from, to, train_type, car, seat);
        break;

    case THSR_ROUND_TRIP:
        THSR_m[date] = THSR(train_no, drive, date, travel, from, to, train_type, car, seat);
        iss >> tmp;
        train_no = BS_lambda::stoi(tmp);
        iss >> tmp;
        drive = BS_lambda::stoi(tmp);
        iss >> date >> train_type >> tmp >> seat;
        car = BS_lambda::stoi(tmp);

        BS_lambda::replace_and_shrink(date, '_', ' ');
        BS_lambda::replace_and_shrink(train_type, '_', ' ');
        BS_lambda::replace_and_shrink(seat, '_', ' ');

        THSR_m[date] = THSR(train_no, drive, date, travel, to, from, train_type, car, seat);
        break;
    }
}
