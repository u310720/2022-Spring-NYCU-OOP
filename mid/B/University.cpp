#include "University.h"
#include "Applicant.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int University::n_universities = 0;
stringstream University::write_buf[3];

const int University::table[5][5] = {{11, 9, 6, 4, 3}, // math
                                    {13, 12, 11, 9, 8}, // chinese
                                    {13, 12, 8, 5, 4}, //english
                                    {13, 12, 8, 6, 5}, // science
                                    {13, 12, 10, 8, 7}}; // society

University::University() { n_universities++; }

University::University(const University &uni)
{
    serial_num = uni.serial_num;
    name = uni.name;
    enrollment_num = uni.enrollment_num;
    memcpy(criteria, uni.criteria, sizeof(uni.criteria));
    memcpy(weight, uni.weight, sizeof(uni.weight));
    n_universities++;
}

University::~University() { n_universities--; }

ostream &operator<<(ostream &out, University &uni)
{
    out << "_University" << endl;
    out << "Number " << setw(4) << setfill('0') << uni.serial_num << endl;
    out << "Name " << uni.name << endl;
    out << "Enrollment Limit " << uni.enrollment_num << endl;

    uni.write_buf[0] << "_University" << endl;
    uni.write_buf[0] << "Number " << setw(4) << setfill('0') << uni.serial_num << endl;
    uni.write_buf[0] << "Name " << uni.name << endl;
    uni.write_buf[0] << "Enrollment Limit " << uni.enrollment_num << endl << endl;

    return out;
}

bool University::cmp(Applicant *a1, Applicant *a2)
{
    double total1 = 0, total2 = 0;
    for(int i = 0; i < 5; i++)
    {
        if(a1->score[i] > 0)
            total1 += weight[i] * a1->score[i];
        if(a2->score[i] > 0)
            total2 += weight[i] * a2->score[i];
    }
    
    // cout << "total: " << a1->serial_num << ":" << total1 << " " << a2->serial_num << ":" << total2 << endl; // debug
    if(total1 == total2)
        return a1->serial_num < a2->serial_num;
    else
        return total1 < total2;
}

void University::get_Rank5(Applicant *my_applicants)
{
    for(int i = 0; i < my_applicants->n_applicants; i++)
        if(my_applicants[i].isQualified(*this))
            candidate.push_back(&my_applicants[i]);
    
    for(int i = 0, size = candidate.size(); i < size - 1; i++)
    {
        int minIndex = i;
        for(int j = i + 1; j < size; j++)
            if(cmp(candidate[minIndex], candidate[j]))
                minIndex = j;
        swap(candidate[i], candidate[minIndex]);
    }

    cout << "_University " << setw(4) << setfill('0') << serial_num << " " << name << " ";
    write_buf[1] << "_University " << setw(4) << setfill('0') << serial_num << " " << name << " ";
    int cnt = 0;
    for(auto &app : candidate)
    {
        if(cnt++ >= 5)
            break;

        cout << " " << setw(4) << setfill('0') << app->serial_num;
        write_buf[1] << " " << setw(4) << setfill('0') << app->serial_num;
    }
    cout << endl;
    write_buf[1] << endl;
}

void University::match_apps()
{
    cout << "_University" << endl;
    cout << "Number " << setw(4) << setfill('0') << serial_num << endl;
    cout << "Name " << name << endl;
    cout << "Match Result ";
    
    write_buf[2] << "_University" << endl;
    write_buf[2] << "Number " << setw(4) << setfill('0') << serial_num << endl;
    write_buf[2] << "Name " << name << endl;
    write_buf[2] << "Match Result";
    
    for(int i = 0, size = registeration.size(); i < enrollment_num && i < size; i++)
    {
        cout << " " << setw(4) << setfill('0') << registeration[i]->serial_num;
        write_buf[2] << " " << setw(4) << setfill('0') << registeration[i]->serial_num;
    }
    cout << endl << endl;
    write_buf[2] << endl << endl;
}
