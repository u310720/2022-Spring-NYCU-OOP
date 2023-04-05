#ifndef __PLAYER_H__
#define __PLAYER_H__

// 一開始，每人1000 foods
// 每一輪，先造人，再造建築
// 移動人的順序為，速度小的優先，速度一樣則ID小的優先

// P1的指令先做，P2後做
// 還有資源就可以繼續執行指令，沒資源了或執行完所有指令了就換對面
// 操作對象按其 ID 從小到大排列。例如，在這個 2D 地圖中，ID 最小的建築對象將首先執行以生成食物（農場 obj.）、村民（房屋 obj.）或士兵（軍營 obj.）

#include "game_object.h"
class GameObject;

#include <map>
using std::map;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

class Player
{
    friend class Barracks;

private:
    stringstream cmdStream;
    string nextCmd;
    int order; // means Player1, Player2, ...
    int food;
    map<int, GameObject *> buildings, humans;

public:
    Player(int order);
    void load_cmd_to_stream(const string &infile);
    bool can_execute_cmd() const;
};

#endif // __PLAYER_H__