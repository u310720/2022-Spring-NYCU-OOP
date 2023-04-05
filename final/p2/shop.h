#ifndef __SHOP_H__
#define __SHOP_H__

#include "food.h"
class Food;

#include "customer.h"
class Customer;

#include "cashier.h"
class Cashier;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <map>
using std::map;

#include <list>
using std::list;

#include <vector>
using std::vector;

class Shop
{
private:
    list<Customer *> queuing_customer;
    map<string, Food> item_map;
    map<string, Cashier> cashier_map;
    map<string, Customer> customer_map;

    void print_queuing_customer() const;

    bool in_this_shop(const string &) const;

    void transfer_to_other_counter(const list<Customer *> &);

    void enter(ifstream &);
    void buy(ifstream &);
    void queue(ifstream &);
    void display();
    void open(ifstream &);
    void checkout(ifstream &);
    void close(ifstream &);

public:
    Shop(const string &infile);
    void scenario(const string &log);
};

#endif // __SHOP_H__