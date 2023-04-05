#ifndef __FARM_H__
#define __FARM_H__

#include "building.h"
class Building;

// 100 HP
// generates 200 foods per round
// needs 1 villager objects
// 如果該對象當前村民總數小於1，農場將重置糧食生產過程
// Farm 爆掉村民死光光
// 蓋一個要 200 food
class Farm : public Building
{
private:
public:
};

#endif // __FARM_H__