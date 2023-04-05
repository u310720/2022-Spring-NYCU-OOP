#include "player.h"

#include <iostream>
#include <fstream>
using namespace std;

Player::Player(int order)
{
    this->order = order;
    food = 1000;
}
void Player::load_cmd_to_stream(const string &infile)
{
    ifstream ifs(infile);
    if (!ifs)
    {
        cerr << "Could not open " << infile << endl;
        return;
    }
    else
        cmdStream << ifs.rdbuf();
}
bool Player::can_execute_cmd() const
{
    if (nextCmd == "house" && food < 100)
        return false;
    else if (nextCmd == "farm" && food < 200)
        return false;
    else if (nextCmd == "archer_barracks" || nextCmd == "spearman_barracks" || nextCmd == "cavalry_barracks" && food < 300)
        return false;

    return true;
}