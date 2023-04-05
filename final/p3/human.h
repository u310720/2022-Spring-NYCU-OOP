#ifndef __HUMAN_H__
#define __HUMAN_H__

// 有多個目標優先順序相同，用下面的特殊值計算公式決定要打哪一格
// 𝐷𝑖𝑓𝑓. 𝑋 = 𝑡𝑎𝑟𝑔𝑒𝑡𝑋 − 𝑙𝑜𝑐𝑎𝑡𝑖𝑜𝑛𝑋
// 𝐷𝑖𝑓𝑓. 𝑌 = 𝑡𝑎𝑟𝑔𝑒𝑡𝑌 − 𝑙𝑜𝑐𝑎𝑡𝑖𝑜𝑛𝑌
// 𝐹(𝑥, 𝑦) = 2 ∗ (𝐷𝑖𝑓𝑓. 𝑋) ∗ |𝐷𝑖𝑓𝑓. 𝑋| + (𝐷𝑖𝑓𝑓. 𝑌) ∗ |𝐷𝑖𝑓𝑓. 𝑌|

#include "game_object.h"
class GameObject;

class Human : public GameObject
{
protected:
    int speed;

public:
    Human();
    Human(int x, int y);
    virtual void move() = 0;
};

#endif // __HUMAN_H__