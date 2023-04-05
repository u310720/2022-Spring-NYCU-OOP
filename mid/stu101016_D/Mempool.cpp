#include "Mempool.hpp"
#include "Transaction.hpp"
#include "Minner.hpp"

Mempool::Mempool(){}

Mempool::~Mempool()
{
    // --------------------- student code ---------------------
    delete []*transArray;
    delete []*minnerArray;
    // ===================== student code =====================
}

Mempool::Mempool(Transaction **transArray, int transArraySize, Minner **minnerArray, int minnerArraySize)
{
    this->transArray = transArray;
    this->transArraySize = transArraySize;
    this->minnerArray = minnerArray;
    this->minnerArraySize = minnerArraySize;

    // initialize each local transaction array (array's size is LOCAL_TRANSVEC_SIZE variable) of each miner
    // --------------------- student code ---------------------
    Transaction *highestFeeTrans = &((*transArray)[0]);
    for(int i = 1; i < transArraySize; i++)
        if((*transArray)[i].fee > highestFeeTrans->fee)
            highestFeeTrans = &((*transArray)[i]);
    // ===================== student code =====================
   
}


void Mempool::delete_specific_transections(Transaction *completedTransArray, int completedTransArraySize)
{
    // delete completed transaction records in Mempool
    // hint: can use deep copy method to replace old transArray
    // --------------------- student code ---------------------
    
    // ===================== student code =====================
}


void Mempool::notify_other_minners(Minner *finishedMinner)
{
    /*
     * notify other miners, 
       stop miners that mine completed transactions 
       and delete completed transactions in mempool
     */   
    // --------------------- student code ---------------------
    
    // ===================== student code =====================
}


void Mempool::update_block_chain()
{   
    // update all miners and check if any miner need to get new local transaction array
    // --------------------- student code ---------------------

    // ===================== student code =====================
}

