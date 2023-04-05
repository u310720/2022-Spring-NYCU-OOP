#ifndef __APPLICANT_H_
#define __APPLICANT_H_

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class University;

class Applicant
{
private:
    static int sumChinese, sumMath;
    static int highestScience, highestEnglish;
    static stringstream write_buf[3];
    
    int serial_num;
    string name;
    int score[5], wishlist[6];
    string admission;
    
    friend class University;

public:
    static int n_applicants;
    Applicant();
    Applicant(const Applicant &);
    ~Applicant();
    bool isQualified(University &uni);
    void match_uni();
    
    friend void read_file(string filename, Applicant** apps, University **unis);
    friend void sort_apps(Applicant* apps); 
    friend ostream &operator<<(ostream &out, Applicant &app);
    friend void match_func(Applicant *apps, University *unis);
    friend void write_file(string filename, Applicant** apps, University** unis);
    
    static void get_Chinese_Avg();
    static void get_Math_Avg();
    static void get_Science_Highest();
    static void get_English_Highest();
};

#endif
