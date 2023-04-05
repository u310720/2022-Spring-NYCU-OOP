#ifndef __HOUSE_H__
#define __HOUSE_H__

#include "building.h"
class Building;

//  50 HP
// 100 food 蓋一個
// new villager's position = (x, y + 1)
class House : public Building
{
private:
public:
    House(); // need 100 foods
    bool can_generate_a_villager() const;
    void generate_a_villager();
};

#endif // __HOUSE_H__