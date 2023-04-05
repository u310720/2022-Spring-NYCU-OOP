#include "shop.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <sstream>
using std::istringstream;

Shop::Shop(const string &infile)
{
    ifstream ifs;
    string line;

    ifs.open(infile);
    if (!ifs)
    {
        cerr << "Error, could not open " << infile << endl;
        return;
    }

    istringstream iss;
    string itemName;
    while (getline(ifs, line))
    {
        iss.str(line);
        iss >> itemName;
        iss.clear();
        item_map.emplace(itemName, line);
    }
}

void Shop::print_queuing_customer() const
{
    auto iter = queuing_customer.cbegin();

    cout << "queue: ";
    if (!queuing_customer.empty())
    {
        const Customer &customer = **iter++;
        cout << customer.get_name();
    }

    while (iter != queuing_customer.cend())
    {
        const Customer &customer = **iter++;
        cout << " <- " << customer.get_name();
    }
    cout << endl;
}

bool Shop::in_this_shop(const string &customerName) const
{
    return customer_map.find(customerName) != customer_map.end();
}

void Shop::transfer_to_other_counter(const list<Customer *> &customers)
{
    queuing_customer.insert(queuing_customer.begin(), customers.begin(), customers.end());
    for (auto &iter : cashier_map)
    {
        if (queuing_customer.empty())
            break;

        Cashier &cashier = iter.second;
        while (cashier.serviceable())
        {
            cashier.recept(queuing_customer.front());
            queuing_customer.erase(queuing_customer.begin());
        }
    }
}

void Shop::enter(ifstream &ifs)
{
    string customerName, gender;
    int age;
    ifs >> customerName >> age >> gender;

    Customer customer;
    if (gender == "M")
        customer = Customer(customerName, age, Person::MALE);
    else // gender == "F"
        customer = Customer(customerName, age, Person::FEMALE);

    customer.go_entering_shop();
    customer_map.emplace(customerName, customer);
}
void Shop::buy(ifstream &ifs)
{
    string customerName, item;
    ifs >> customerName >> item;

    Customer &customer = customer_map.find(customerName)->second;
    Food &f = item_map.find(item)->second;

    customer.go_shopping();
    if (customer.can_take_more())
        customer.buy(f);
    else
        cout << customerName << " can't buy anymore!" << endl;
}
void Shop::queue(ifstream &ifs)
{
    string customerName;
    ifs >> customerName;

    Customer &customer = customer_map.find(customerName)->second;

    customer.go_queuing();
    for (auto &iter : cashier_map)
    {
        Cashier &cashier = iter.second;
        if (cashier.serviceable())
        {
            cashier.recept(&customer);
            return;
        }
    }
    queuing_customer.push_back(&customer);
}
void Shop::display()
{
    print_queuing_customer();
    for (const auto &iter : cashier_map)
    {
        const Cashier &cashier = iter.second;
        cashier.print_counter();
    }
}
void Shop::open(ifstream &ifs)
{
    int age;
    string cashierName, gender, qualification;
    ifs >> cashierName >> age >> gender >> qualification;

    Cashier cashier;
    if (gender == "F")
    {
        if (qualification == "senior")
            cashier = Cashier(cashierName, age, Person::FEMALE, Cashier::SENIOR);
        else // qualification == "junior"
            cashier = Cashier(cashierName, age, Person::FEMALE, Cashier::JUNIOR);
    }
    else // gender == "M"
    {
        if (qualification == "senior")
            cashier = Cashier(cashierName, age, Person::MALE, Cashier::SENIOR);
        else // qualification == "junior"
            cashier = Cashier(cashierName, age, Person::MALE, Cashier::JUNIOR);
    }

    cashier.open_counter();
    while (cashier.serviceable() && !queuing_customer.empty())
    {
        cashier.recept(queuing_customer.front());
        queuing_customer.pop_front();
    }

    cashier_map.emplace(cashier.get_name(), cashier);
}
void Shop::checkout(ifstream &ifs)
{
    string cashierName, customerName;
    ifs >> cashierName >> customerName;

    Customer &customer = customer_map.find(customerName)->second;
    Cashier &cashier = cashier_map.find(cashierName)->second;

    if (!in_this_shop(customerName) || !customer.at_this_counter(cashier))
        cout << customerName << " isn't at " << cashierName << "'s counter!" << endl;
    else
    {
        cashier.checkout(customer);
        customer_map.erase(customerName);

        if (!queuing_customer.empty())
        {
            Customer *nextCustomer = queuing_customer.front();
            cashier.recept(nextCustomer);
            queuing_customer.pop_front();
        }
    }
}
void Shop::close(ifstream &ifs)
{
    string cashierName;
    ifs >> cashierName;

    auto iter = cashier_map.find(cashierName);
    Cashier &cashier = iter->second;

    cashier.close_counter();
    if (cashier.someone_at_counter())
        transfer_to_other_counter(cashier.get_serving_customers());

    cashier_map.erase(iter);
}

void Shop::scenario(const string &log)
{
    ifstream ifs;
    string action;

    ifs.open(log);
    while (ifs >> action)
    {
        if (action == "enter")
            enter(ifs);
        else if (action == "buy")
            buy(ifs);
        else if (action == "queue")
            queue(ifs);
        else if (action == "display")
            display();
        else if (action == "open")
            open(ifs);
        else if (action == "checkout")
            checkout(ifs);
        else if (action == "close")
            close(ifs);
    }
}