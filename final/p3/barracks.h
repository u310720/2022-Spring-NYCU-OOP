#ifndef __BARRACKS_H__
#define __BARRACKS_H__

#include "player.h"
class Player;

#include "building.h"
class Building;

#include "soldier.h"
class Soldier;

#include "villager.h"
class Villager;

// 300 HP OK
// 需要 300 food蓋一個 OK
// 三種兵 Archer, Cavalry or spearman OK
// 每兩輪，它會生成 1 個特定類型的士兵並花費 300 食物 X
// 如果當前的食物庫存少於 300，兵營將暫停生成士兵的過程 OK
// 新士兵的位置為(x, y + 1) ，(x, y + 1)是空的才能繼續產兵 OK
// 需要兩個村民，如果少於兩個會重置產兵過程 OK
// Barracks 爆掉村民死光光 OK
class Barracks : public Building
{
private:
    Player &player;
    int property;
    int roundCnt; // every two rounds generate one soldier
    Villager *laborers[2];

    void all_laborers_dead();

public:
    enum PROPERTY
    {
        ARCHER_BARRACKS,
        CAVALRY_BARRACKS,
        SPEARMAN_BARRACKS,
    };
    Barracks(int x, int y, int property, Player &Player); // will cost 300 foods
    ~Barracks();
    bool can_generate_a_soldier() const;
    void generate_a_soldier();
};

#endif // __BARRACKS_H__