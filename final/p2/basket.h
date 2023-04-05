#ifndef __BASKET_H__
#define __BASKET_H__

#include "food.h"
class Food;

#include <map>
using std::map;

#include <iostream>
using std::ostream;

class Basket
{
private:
    int nItem = 0;
    map<Food, int> content;

public:
    void put_in(const Food &);
    Food take_out();
    int n_item() const;
    int get_amount() const;
    int get_amount(const Food &) const;
    const map<Food, int> &get_content() const;

    friend ostream &operator<<(ostream &, const Basket &);
};

// template <typename Obj>
// class Basket
// {
// private:
//     int nItem = 0;
//     map<const Obj, int> content;

// public:
//     void put_in(const Obj &);
//     Obj take_out();
//     int n_item() const;
// };

#endif // __BASKET_H__