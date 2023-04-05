#include "customer.h"

Customer::Customer()
{
}
Customer::Customer(const string &name, int age, bool gender) : Person(name, age, gender), Basket()
{
    action = UNKNOW;
}

void Customer::go_entering_shop()
{
    action = ENTER;
}
void Customer::go_shopping()
{
    action = SHOPING;
}
void Customer::go_queuing()
{
    action = QUEUING;
}
void Customer::go_checking_out()
{
    action = CHECKINGOUT;
}
void Customer::go_away()
{
    action = LEAVE;
}

bool Customer::is_entering_shop()
{
    return action == ENTER;
}
bool Customer::is_shopping()
{
    return action == SHOPING;
}
bool Customer::is_queuing()
{
    return action == QUEUING;
}
bool Customer::is_checking_out()
{
    return action == CHECKINGOUT;
}
bool Customer::is_away()
{
    return action == LEAVE;
}

void Customer::buy(const Food &f)
{
    put_in(f);
}
bool Customer::can_take_more() const
{
    if (is_child())
        return n_item() < 3;
    else if (is_women())
        return n_item() < 4;
    else // is_men()
        return n_item() < 5;
}

bool Customer::at_this_counter(const Cashier &cashier) const
{
    for (const auto &iter : cashier.get_serving_customers())
        if (this == iter)
            return true;
    return false;
}