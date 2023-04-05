#include <iostream>

#include "Minner.hpp"
#include "Mempool.hpp"
#include "functions.hpp"
#include "Transaction.hpp"

using namespace std;

/*
 * Attension:
 *   You do not need to change this file, as TA will use its own in the demo.
 */
int main(int argc, char *argv[])
{
    Transaction *transArray;
    int transArraySize;
    Minner *minnerArray;
    int minnerArraySize;

    // create objects from input file
    parse_tranfsaction_file(argv[1], &transArray, transArraySize); 
    parse_minner_file(argv[2], &minnerArray, minnerArraySize);

    // start to simulate mining process of block chain
    Mempool *mem = new Mempool(&transArray, transArraySize, &minnerArray, minnerArraySize);    
    for (int timestamp = 0; timestamp < stoi(string(argv[3])); timestamp++) {        
        mem->update_block_chain();
    }
    cout << minnerArraySize << endl; // debug
    for (int i = 0; i < minnerArraySize; i++) {
        get_minner_revenue(&minnerArray[i]);
    }

    delete mem;

    return 0;
}
