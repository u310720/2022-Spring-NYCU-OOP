#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "human.h"
class Hunam;

// 如果一個敵方物體（例如人或建築物）在該士兵的攻擊範圍內或他無法移動，他將保持不動
// 如果士兵的攻擊範圍內沒有敵對物體（人類或建築物），他將移動到距離最短歐幾里得距離的物體。如果許多敵對物體具有相同的最小歐幾里得距離，則該士兵將接近 ID 最小的那個。
// 攻擊範圍內有多個目標打最近的那個，距離相同打ID最小的那個，沒有目標這一輪就不攻擊
class Soldier : public Human
{
private:
    int title;
    int attack;

    enum TITLE
    {
        ARCHER,
        CAVALRY,
        SPEARMAN
    };

public:
    Soldier();
    Soldier(int x, int y);
    void being_archer();   //  150 HP, 3 speed points, 30 base attack points
    void being_cavalry();  //  300 HP, 2 speed points, 60 base attack points
    void being_spearman(); // 500 HP, 4 speed points, 50 base attack points
    void move();
};

#endif // __SOLDIER_H__