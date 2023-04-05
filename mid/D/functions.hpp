#ifndef _FUNCTIONS
#define _FUNCTIONS

#include <iostream>
#include <string>
#include "Minner.hpp"
#include "Transaction.hpp"

using namespace std;


// ------------ maybe this file need to add something --------------------
// --------------------- student code ---------------------
class Minner; // why #include Minner.hpp didn't declare Minner?
// ===================== student code =====================

void parse_tranfsaction_file(string filePath, Transaction **transArray, int &transArraySize);
void parse_minner_file(string filePath, Minner **minnerArray, int &minnerArraySize);
void get_minner_revenue(Minner *minner);


#endif
