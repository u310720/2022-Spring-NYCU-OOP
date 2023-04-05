#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "functions.hpp"
#include "Minner.hpp"
#include "Transaction.hpp"

using namespace std;

void parse_tranfsaction_file(string filePath, Transaction **transArray, int &transArraySize)
{
    // use dynamic array to store transactions from transction file    
    // --------------------- student code ---------------------
    ifstream ifs(filePath);
    if(!ifs)
    {
        cout << "can't open " << filePath << endl;
        exit(1);
    }

    string line, id, buyer, seller;
    double fee, coinAmount, usDollar;
    istringstream iss;
    vector<Transaction> tVec;
    while(getline(ifs, line))
    {
        iss.str(line);
        iss >> id >> fee >> buyer >> seller >> coinAmount >> usDollar;
        iss.clear();
        tVec.push_back(Transaction(id, fee, buyer, seller, coinAmount, usDollar));
    }
    ifs.close();
    
    transArraySize = tVec.size();
    *transArray = new Transaction[transArraySize];
    for(int i = 0; i < transArraySize; i++)
        (*transArray)[i] = tVec[i];
    // ===================== student code =====================
}

void parse_minner_file(string filePath, Minner **minnerArray, int &minnerArraySize)
{
    // use dynamic array to store miners from miner file
    // --------------------- student code ---------------------
    ifstream ifs(filePath);
    if(!ifs)
    {
        cout << "can't open " << filePath << endl;
        exit(1);
    }

    string line;
    bool workType;
    int id, computingPower;
    istringstream iss;
    vector<Minner> mVec;
    while(getline(ifs, line))
    {
        iss.str(line);
        iss >> id >> workType >> computingPower;
        iss.clear();
        mVec.push_back(Minner(id, workType, computingPower));
    }
    ifs.close();

    minnerArraySize = mVec.size();
    *minnerArray = new Minner[minnerArraySize];
    for(int i = 0; i < minnerArraySize; i++)
        (*minnerArray)[i] = mVec[i];
    // ===================== student code =====================
}


void get_minner_revenue(Minner *minner)
{
    // hint: this function can directly access private member of Miner class.
    cout << "Miner " << minner->id << "'s revenue: " << minner->revenue << endl;
}
