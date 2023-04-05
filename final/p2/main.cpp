#include "shop.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    const string in1 = argc < 2 ? "grocery.in" : argv[1];
    const string in2 = argc < 3 ? "scenario.in" : argv[2];

    Shop g(in1);
    g.scenario(in2);

    return 0;
}