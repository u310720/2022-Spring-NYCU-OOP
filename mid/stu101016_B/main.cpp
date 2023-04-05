#define Q1
#define Q2
#define Q3

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

#include "Applicant.h"
#include "University.h"

using namespace std;

// Q1
void read_file(string filename, Applicant** apps, University** unis)
{
    ifstream ifs(filename);
    if(!ifs)
    {
        cout << "ERROR" << endl;
        exit(1);
    }

    string line, tmp;
    istringstream iss;
    vector<Applicant> VApp;
    vector<University> VUni;

    int &sumCh = Applicant::sumChinese, 
        &sumMath = Applicant::sumMath, 
        &highSci = Applicant::highestScience, 
        &highEng = Applicant::highestEnglish;
    while(getline(ifs, line))
    {
        for(auto &c : line)
            if(c == ',' || c == '(' || c == ')')
                c = ' ';
        iss.str(line);
        
        iss >> tmp;
        if(tmp[0] == 'U')
        {
            University U;
            iss >> U.serial_num >> U.name;
            for(int i = 0; i < 5; i++)
            {
                iss >> tmp;
                U.criteria[i] = tmp == "X" ? -1 : U.table[i][4 - stoi(tmp)];
            }
            for(int i = 0; i < 5; i++)
                iss >> U.weight[i];
            iss >> U.enrollment_num;
            VUni.push_back(U);
        }
        else if(tmp[0] == 'A')
        {
            Applicant A;
            iss >> A.serial_num >> A.name >> tmp;
            A.name.append(" ").append(tmp);
            for(int i = 0; i < 5; i++)
            {
                iss >> tmp;
                A.score[i] = tmp == "X" ? -1 : stoi(tmp);
                switch(i)
                {
                    case 0:
                        sumMath += A.score[0] > 0 ? A.score[0] : 0;
                        break;
                    case 1:
                        sumCh += A.score[1] > 0 ? A.score[1] : 0;
                        break;
                    case 2:
                        highEng = highEng < A.score[2] ? A.score[2] : highEng;
                        break;
                    case 3:
                        highSci = highSci < A.score[3] ? A.score[3] : highSci;
                        break;
                }
            }
            for(int i = 0; i < 6; i++)
                if(!(iss >> A.wishlist[i]))
                    A.wishlist[i] = -1;
                   
            VApp.push_back(A);
        }
        iss.clear();
    }
    ifs.close();
     
    *apps = new Applicant[Applicant::n_applicants];
    for(int i = 0; i < Applicant::n_applicants - VApp.size(); i++)
        (*apps)[i] = VApp[i];
    *unis = new University[University::n_universities];
    for(int i = 0; i < University::n_universities - VUni.size(); i++)
        (*unis)[i] = VUni[i];
   
} 
// Q1
void sort_apps(Applicant* apps)
{
    sort(apps, apps + Applicant::n_applicants, [](Applicant &a1, Applicant &a2){ return a1.serial_num < a2.serial_num; });
}
// Q1
void sort_unis(University* unis)
{
    sort(unis, unis + University::n_universities, [](University &u1, University &u2){ return u1.serial_num < u2.serial_num; });
}

// Q3 You need to delete the memory in the write file
void match_func(Applicant *apps, University *unis)
{
    map<int, University *> uniMap;
    for(int i = 0; i < unis->n_universities; i++)
        uniMap[unis[i].serial_num] =  &unis[i]; 
    
    // update wishlist based on qualification
    for(int i = 0; i < apps->n_applicants; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(apps[i].wishlist[0] == -1)
                break;

            University *uni = uniMap.find(apps[i].wishlist[0])->second;
            if(apps[i].isQualified(*uni))
                break;

            apps[i].wishlist[0] = -1;
            rotate(begin(apps[i].wishlist), begin(apps[i].wishlist) + 1, end(apps[i].wishlist));
        }
    }

    // update candidate based on wishlist
    for(int i = 0; i < unis->n_universities; i++)
    {
        for(int j = 0; j < unis[i].candidate.size();)
        {
            bool flag = true;
            for(int k = 0; k < 6; k++)
            {
                if(unis[i].candidate[j]->wishlist[k] == -1)
                    break;
                if(unis[i].candidate[j]->wishlist[k] == unis[i].serial_num)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
                unis[i].candidate.erase(unis[i].candidate.begin() + j);
            else
                j++;
        }
    }

    

    vector<int> regSize(unis->n_universities, 0);
    for(int wishOrder = 0; wishOrder < 6; wishOrder++)
    {
        for(int i = 0; i < unis->n_universities; i++)
        {
            for(auto &candi : unis[i].candidate)
            {
                if(candi->wishlist[0] == unis[i].serial_num) // if candi's current first order is unis[i] do ...
                {
                    if(regSize[i] == unis[i].enrollment_num)
                    {
                        candi->wishlist[0] = -1;
                        rotate(begin(candi->wishlist), begin(candi->wishlist) + 1, end(candi->wishlist)); // left circular shift 1
                    }
                    else
                    {
                        candi->admission = unis[i].name;
                        unis[i].registeration.push_back(candi);
                        memset(candi->wishlist, -1, sizeof(candi->wishlist));
                        regSize[i]++;
                    }
                }
            }
        }
    }
}
void write_file(string filename, Applicant** apps, University** unis)
{
    ofstream ofs(filename);
    if(!ofs)
    {
        cout << "ofs error" << endl;
        return;
    }

#ifdef Q1
    ofs << (*apps)->n_applicants << endl;
    ofs << (*apps)->write_buf[0].str();
    ofs << (*unis)->n_universities << endl;
    ofs << (*unis)->write_buf[0].str();
#endif

#ifdef Q2
    ofs << (*unis)->write_buf[1].str();
#endif

#ifdef Q3
    ofs << (*apps)->write_buf[2].str();
    ofs << (*unis)->write_buf[2].str();
#endif

    ofs.close();
    delete []*apps;
    delete []*unis;
}

int main(int argc, char* argv[]){

    Applicant* my_applicants;
    University* my_universities;

    if(argc < 2){
        cout << "No input file provided." << endl;
        return -1;
    }
    if(argc < 3){
        cout << "No output file provided." << endl;
        return -1;
    }

    //Q1
    read_file(argv[1], &my_applicants, &my_universities);
    sort_apps(my_applicants);
    sort_unis(my_universities);

    cout << my_applicants -> n_applicants << endl;
    for(int i = 0; i < my_applicants -> n_applicants; i++){
        cout << my_applicants[i] << endl;
    }

    cout << my_universities -> n_universities << endl;
    for(int i = 0; i < my_universities -> n_universities; i++){
        cout << my_universities[i] << endl;
    }

    my_applicants->get_Chinese_Avg();
    my_applicants->get_Math_Avg();
    my_applicants->get_Science_Highest();
    my_applicants->get_English_Highest();

    //Q2
    for(int i = 0; i < my_universities -> n_universities; i++){
        my_universities[i].get_Rank5(my_applicants);
    }	

    //Q3
    match_func(my_applicants, my_universities);
    for(int i = 0; i < my_applicants -> n_applicants; i++){
        my_applicants[i].match_uni();
    }

    for(int i = 0; i < my_universities -> n_universities; i++){
        my_universities[i].match_apps();
    }
    write_file(argv[2], &my_applicants, &my_universities);
}  
