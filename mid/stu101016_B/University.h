#ifndef __UNIVERSITY_H_
#define __UNIVERSITY_H_

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


class Applicant;

class University
{
private:
    static const int table[5][5];
    static stringstream write_buf[3];
    
    int serial_num;
    string name;
    int criteria[5];
    double weight[5];
    int enrollment_num;
    vector<Applicant *> candidate;
    vector<Applicant *> registeration;
    
    bool cmp(Applicant *a1, Applicant *a2);
    
    friend class Applicant;
    
public:
    static int n_universities;
    
    University();
    University(const University &);
    ~University();
    void get_Rank5(Applicant *my_applicants);
    void match_apps();
    
    friend void read_file(string filename, Applicant** apps, University **unis);
    friend void sort_unis(University* unis);
    friend void match_func(Applicant *apps, University *unis);
    friend void write_file(string filename, Applicant** apps, University** unis);
    
    friend ostream &operator<<(ostream &out, University &uni);
};

#endif
