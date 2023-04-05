#include "basket.h"

#include <iostream>
using std::endl;

#include <iomanip>
using std::right;
using std::setw;

void Basket::put_in(const Food &obj)
{
    ++nItem;
    auto iter = content.find(obj);
    if (iter != content.end())
        ++iter->second;
    else
        content.emplace(obj, 1);
}
Food Basket::take_out()
{
    --nItem;
    --content.begin()->second;
    Food tmp = content.begin()->first;
    if (content.begin()->second == 0)
        content.erase(content.begin());
    return tmp;
}
int Basket::n_item() const
{
    return nItem;
}
int Basket::get_amount() const
{
    int amount = 0, price, quantity;
    for (const auto &item : content)
    {
        price = item.first.get_price();
        quantity = item.second;
        amount += price * quantity;
    }
    return amount;
}
int Basket::get_amount(const Food &food) const
{
    return content.find(food)->second;
}
const map<Food, int> &Basket::get_content() const
{
    return content;
}

// template <typename Obj>
// void Basket<Obj>::put_in(const Obj &obj)
// {
//     ++nItem;
//     auto iter = content.find(obj);
//     if (iter != content.end())
//         ++iter->second;
//     else
//         content.emplace(obj, 1);
// }
// template <typename Obj>
// Obj Basket<Obj>::take_out()
// {
//     --nItem;
//     --content.begin()->second;
//     Obj tmp = *content.begin();
//     if (content.begin()->second == 0)
//         content.erase(content.begin());
//     return tmp;
// }
// template <typename Obj>
// int Basket<Obj>::n_item() const
// {
//     return nItem;
// }