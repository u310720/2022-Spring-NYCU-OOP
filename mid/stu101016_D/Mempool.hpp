#ifndef _MEMPOOL
#define _MEMPOOL

#include <iostream>
#include <vector>

#include "Transaction.hpp"
#include "Minner.hpp"

using namespace std;

// you need to add something to make it compile success
// --------------------- student code ---------------------   
class Minner; // why #include Minner.hpp didn't declare Minner?

class Mempool
{
private:    
    Transaction **transArray;
    int transArraySize; 
    Minner **minnerArray;
    int minnerArraySize;
    void delete_specific_transections(Transaction *completedTransArray, int completedTransArraySize);
    void notify_other_minners(Minner *finishedMinner);
public:       
    Mempool();     
    Mempool(Transaction **transArray, int transArraySize, Minner **minnerArray, int minnerArraySize);
    ~Mempool();
    void update_block_chain();
};

// ===================== student code =====================
#endif
