#include "soldier.h"

Soldier::Soldier()
{
}
Soldier::Soldier(int x, int y) : Human(x, y)
{
}
void Soldier::being_archer() //  150 HP, 3 speed points, 30 base attack points
{
    title = ARCHER;
    HP = 150;
    speed = 3;
    attack = 30;
}
void Soldier::being_cavalry() //  300 HP, 2 speed points, 60 base attack points
{
    title = CAVALRY;
    HP = 300;
    speed = 2;
    attack = 60;
}
void Soldier::being_spearman() // 500 HP, 4 speed points, 50 base attack points
{
    title = SPEARMAN;
    HP = 500;
    speed = 4;
    attack = 50;
}
void Soldier::move()
{
}