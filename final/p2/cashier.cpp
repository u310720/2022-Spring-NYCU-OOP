#include "cashier.h"

#include <string>
using std::to_string;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::left;
using std::right;
using std::setw;

Cashier::Cashier() : Person()
{
    action = UNKNOW;
}
Cashier::Cashier(const string &name, int age, bool gender, bool title) : Person(name, age, gender)
{
    this->title = title;
    action = UNKNOW;
}
bool Cashier::is_senior() const
{
    return title == SENIOR;
}
bool Cashier::is_junior() const
{
    return title == JUNIOR;
}
void Cashier::open_counter()
{
    action = OPEN;
}
void Cashier::close_counter()
{
    action = CLOSE;
}
void Cashier::print_basket(const Basket &b) const
{
    // Example
    // |     donut|         1|        40|        40|
    // |     apple|         1|        10|        10|
    // |    orange|         1|        20|        20|
    for (const auto &item : b.get_content())
    {
        const Food &food = item.first;
        int quantity = item.second;
        cout << "|" << right << setw(10) << food.get_name() << "|" << right << setw(10) << quantity;
        cout << "|" << right << setw(10) << food.get_price() << "|" << right << setw(10) << food.get_price() * quantity;
        cout << "|" << endl;
    }
}
void Cashier::print_receipt(const Customer &customer) const
{
    // +-------------------------------------------+
    // |Name: Sam                                  |
    // +-------------------------------------------+
    // |      item|  quantity|unit price|     total|
    // |     donut|         1|        40|        40|
    // |     apple|         1|        10|        10|
    // |    orange|         1|        20|        20|
    // |                           total amount: 70|
    // +-------------------------------------------+

    cout << "+-------------------------------------------+" << endl;
    cout << "|Name: " << left << setw(37) << customer.get_name() << "|" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << "|      item|  quantity|unit price|     total|" << endl;
    print_basket((const Basket &)customer);

    int total = customer.get_amount();
    int nDigit = to_string(total).length();
    cout << "|" << right << setw(43 - nDigit) << "total amount: " << total << "|" << endl;
    cout << "+-------------------------------------------+" << endl;
}

bool Cashier::serviceable() const
{
    if (is_junior())
        return at_counter.size() < 2;
    else if (is_senior())
        return at_counter.size() < 3;
    else
        return false;
}
void Cashier::recept(Customer *customer)
{
    customer->go_checking_out();
    at_counter.push_back(customer);
}
void Cashier::checkout(const Customer &customer)
{
    print_receipt(customer);
    for (auto iter = at_counter.begin(); iter != at_counter.end(); ++iter)
    {
        if (*iter == &customer)
        {
            at_counter.erase(iter);
            break;
        }
    }
}
bool Cashier::someone_at_counter() const
{
    return !at_counter.empty();
}

const list<Customer *> &Cashier::get_serving_customers() const
{
    return at_counter;
}

void Cashier::print_counter() const
{
    // Cherry's counter: Sam Yuri
    cout << name << "'s counter: ";
    for (const auto &customer : at_counter)
        cout << customer->get_name() << " ";
    cout << endl;
}