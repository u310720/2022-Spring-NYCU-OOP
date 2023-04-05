#ifndef __FOOD_H__
#define __FOOD_H__

#include <string>
using std::string;

class Food
{
private:
    string name;
    int type;
    int price;
    int weight;

public:
    enum TYPE
    {
        BREAD,
        FRUIT,
        DRINK,
        UNKNOW
    };
    Food(const string &line);
    string get_name() const;
    int get_price() const;
    int get_weight() const;
    bool operator<(const Food &) const;
};

#endif // __FOOD_H__
