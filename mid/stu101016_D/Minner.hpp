#ifndef _MINNER
#define _MINNER

#include <iostream>
#include <string>

#include "Transaction.hpp"
#include "Mempool.hpp"
#include "functions.hpp"


using namespace std;

// you need to add something to make it compile success
// --------------------- student code ---------------------   
class Mempool;

class Minner
{
private:        
    int id;
    double revenue;
    bool workType; //1: Ascending order, 0: Descending      
    int computingPower;    
    int miningProcessTimer;   // value range: 1~8
    Transaction *localTransArr; 
    void set_new_localTransArr(Transaction *transVec, int transVecSize);
    bool check_transactions_in_localTransArr(Transaction *completedTransArr, int completedTransArrSize);
    void clear_localTransArr(bool changeMinnerType);
    void get_mining_process_reward();        
    bool update_mining_process();  
    void swap_transaction(Transaction *m1, Transaction *m2);    
    friend void parse_minner_file(string filePath, Minner **minnerArray, int &minnerArraySize);
    friend void get_minner_revenue(Minner *minner);
    friend class Mempool;

public:        
    int LOCAL_TRANSVEC_SIZE = 2;    
    Minner();
    Minner(int id, bool workType, int computingPower);
    ~Minner();
    void set_id(int id);
    void set_workType(int workType);
    void set_computingPower(int computingPower);
};
// ===================== student code =====================
#endif
