#include "player.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    const string cmdList1 = argc < 2 ? "p1_cmd_list.txt" : argv[1];
    const string cmdList2 = argc < 3 ? "p2_cmd_list.txt" : argv[2];

    Player p1(1), p2(2);
    p1.load_cmd_to_stream(cmdList1);
    p2.load_cmd_to_stream(cmdList2);

    GameObject g;

    while (1)
    {
        if (p1.can_execute_cmd())
        {
        }
        else if (p2.can_execute_cmd())
        {
        }
        else
            break;
    }

    return EXIT_SUCCESS;
}