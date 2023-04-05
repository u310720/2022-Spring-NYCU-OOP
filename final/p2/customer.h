#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include "person.h"
class Person;

#include "cashier.h"
class Cashier;

#include "food.h"
class Food;

#include "basket.h"
class Basket;

class Customer : public Person, public Basket
{
private:
    int action;

    enum ACTION
    {
        ENTER,
        SHOPING,
        QUEUING,
        CHECKINGOUT,
        LEAVE,
        UNKNOW
    };

public:
    Customer();
    Customer(const string &name, int age, bool gender);

    void go_entering_shop();
    void go_shopping();
    void go_queuing();
    void go_checking_out();
    void go_away();

    bool is_entering_shop();
    bool is_shopping();
    bool is_queuing();
    bool is_checking_out();
    bool is_away();

    void buy(const Food &);
    bool can_take_more() const;

    bool at_this_counter(const Cashier &) const;
};

#endif // __CUSTOMER_H__
