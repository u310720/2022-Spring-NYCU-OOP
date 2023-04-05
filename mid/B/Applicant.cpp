#include "Applicant.h"
#include "University.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
using namespace std;

int Applicant::n_applicants = 0;
int Applicant::sumMath = 0;
int Applicant::sumChinese = 0;
int Applicant::highestEnglish = 0;
int Applicant::highestScience = 0;
stringstream Applicant::write_buf[3];


Applicant::Applicant() { n_applicants++; }

Applicant::Applicant(const Applicant &app)
{
    serial_num = app.serial_num;
    name = app.name;
    memcpy(score, app.score, sizeof(app.score));
    memcpy(wishlist, app.wishlist, sizeof(app.wishlist));
    n_applicants++;
}

Applicant::~Applicant() { n_applicants--; }

void Applicant::get_Chinese_Avg()
{
    cout << "Chinese Average: " << (double)sumChinese / n_applicants << endl;
    University::write_buf[0] << "Chinese Average: " << (double)sumChinese / n_applicants << endl;
}

void Applicant::get_Math_Avg()
{
    cout << "Math Average: " << (double)sumMath / n_applicants << endl; 
    University::write_buf[0] << "Math Average: " << (double)sumMath / n_applicants << endl;
}

void Applicant::get_Science_Highest()
{
    cout << "Science Highest: " << highestScience << endl;
    University::write_buf[0] << "Science Highest: " << highestScience << endl;
}

void Applicant::get_English_Highest()
{
    cout << "English Highest: " << highestEnglish << endl;
    University::write_buf[0] << "English Highest: " << highestEnglish << endl;
}

ostream &operator<<(ostream &out, Applicant &app)
{
    out << "_Applicant" << endl;
    out << "Number " << setw(4) << setfill('0') << app.serial_num << endl;
    out << "Name " << app.name << endl;
    
    int total = 0, nSubject = 0;
    for(int i = 0; i < 5; i++)
    {
        if(app.score[i] == -1)
            continue;

        switch(i)
        {
            case 0:
                out << "Math ";
                break;
            case 1:
                out << "Chinese ";
                break;
            case 2:
                out << "English ";
                break;
            case 3:
                out << "Science ";
                break;
            case 4:
                out << "Society ";
                break;
        }
        out << app.score[i] << endl;
        total += app.score[i];
        nSubject++;
    }
    out << "Total " << total << "/" << 15 * nSubject << endl;
    
    
    app.write_buf[0] << "_Applicant" << endl;
    app.write_buf[0] << "Number " << setw(4) << setfill('0') << app.serial_num << endl;
    app.write_buf[0] << "Name " << app.name << endl;
    
    for(int i = 0; i < 5; i++)
    {
        if(app.score[i] == -1)
            continue;

        switch(i)
        {
            case 0:
                app.write_buf[0] << "Math ";
                break;
            case 1:
                app.write_buf[0] << "Chinese ";
                break;
            case 2:
                app.write_buf[0] << "English ";
                break;
            case 3:
                app.write_buf[0] << "Science ";
                break;
            case 4:
                app.write_buf[0] << "Society ";
                break;
        }
        app.write_buf[0] << app.score[i] << endl;
    }
    app.write_buf[0] << "Total " << total << "/" << 15 * nSubject << endl << endl;

    return out;
}

bool Applicant::isQualified(University &uni)
{
    for(int i = 0; i < 5; i++)
        if(score[i] < uni.criteria[i])
            return false;
    return true;
}

void Applicant::match_uni()
{
    cout << "_Applicant" << endl;
    cout << "Number " << setw(4) << setfill('0') << serial_num << endl;
    cout << "Name " << name << endl;
    cout << "Match Result " << admission << endl << endl;

    write_buf[2] << "_Applicant" << endl;
    write_buf[2] << "Number " << setw(4) << setfill('0') << serial_num << endl;
    write_buf[2] << "Name " << name << endl;
    write_buf[2] << "Match Result " << admission << endl << endl;
}
