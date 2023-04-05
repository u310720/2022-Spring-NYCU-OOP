#ifndef __CASHIER_H__
#define __CASHIER_H__

#include "person.h"
class Person;

#include "basket.h"
class Basket;

#include "customer.h"
class Customer;

#include <string>
using std::string;

#include <list>
using std::list;

class Cashier : public Person
{
private:
    bool title;
    int action;
    list<Customer *> at_counter;

    enum ACTION
    {
        OPEN,
        CHECKOUT,
        CLOSE,
        UNKNOW
    };
    void print_basket(const Basket &) const;
    void print_receipt(const Customer &) const;

public:
    enum TITLE
    {
        SENIOR, // a senior cashier can help three customers to check out at one time
        JUNIOR, // a junior cashier can help two customers to check out at one time
    };

    Cashier();
    Cashier(const string &name, int age, bool gender, bool title);

    bool is_senior() const;
    bool is_junior() const;

    void open_counter();
    void close_counter();

    bool serviceable() const;
    void recept(Customer *);
    void checkout(const Customer &); // if customer is not at this counter, then return false
    bool someone_at_counter() const;

    const list<Customer *> &get_serving_customers() const;

    void print_counter() const;
};

#endif // __CASHIER_H__
