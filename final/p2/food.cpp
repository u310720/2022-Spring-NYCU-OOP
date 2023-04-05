#include "food.h"

#include <sstream>
using std::istringstream;

Food::Food(const string &line)
{
    static istringstream iss;
    static string sType;

    iss.clear();
    sType.clear();
    iss.str(line);

    iss >> name >> sType >> price >> weight;
    if (sType == "fruit")
        type = FRUIT;
    else if (sType == "bread")
        type == BREAD;
    else if (sType == "drink")
        type = DRINK;
    else
        type = UNKNOW;
}
string Food::get_name() const
{
    return name.c_str();
}
int Food::get_price() const
{
    return price;
}
int Food::get_weight() const
{
    return weight;
}
bool Food::operator<(const Food &f) const
{
    if (type == f.type)
    {
        if (weight == f.weight)
            return name < f.name;
        else
            return weight < f.weight;
    }
    else
        return type < f.type;
}