#ifndef __VILLAGER_H__
#define __VILLAGER_H__

#include "human.h"
class Human;

#include "building.h"
class Building;

#include <list>
using std::list;

// 如果沒有農場或兵營對象需要勞動力，該村民將保持靜止
// 村民會自動移動到最近的需要勞動力的農場或兵營。如果多個農場 / 營房對象具有相同的最短歐幾里得距離，則該村民將接近 ID 最小的那個。
class Villager : public Human
{
private:
    bool inBuilding;
    list<Building *> near_building;

public:
    Villager();
    Villager(int x, int y, Building *source);
    void move();
};

#endif // __VILLAGER_H__