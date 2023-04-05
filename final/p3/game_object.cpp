#include "game_object.h"

#include <iostream>
#include <cmath>
using namespace std;

int GameObject::ID_count = 0;
GameObject *GameObject::gameMap[100][100] = {nullptr};

GameObject::GameObject()
{
}
GameObject::GameObject(int x, int y)
{
    this->x = x;
    this->y = y;
    ID = ID_count++;
    if (is_available_at(x, y))
        go_occupy(x, y);
}

GameObject::~GameObject()
{
    disappear_from_the_map();
}
void GameObject::disappear_from_the_map()
{
    if (!is_available_at(x, y))
        gameMap[y][x] = nullptr;
}

bool GameObject::is_available_at(int x, int y) const
{
    if (x < 0 || y < 0 || x >= 100 || y >= 100)
        return false;
    else
        return gameMap[y][x] == nullptr;
}
void GameObject::go_occupy(int x, int y)
{
    gameMap[y][x] = this;
}
void GameObject::go_away_from(int x, int y)
{
    gameMap[y][x] = nullptr;
}

double GameObject::Euclidean_distance(const GameObject &obj1, const GameObject &obj2) const
{
    int deltaX = obj1.x - obj2.x, deltaY = obj1.y - obj2.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}
double GameObject::Euclidean_distance(const GameObject *obj1, const GameObject *obj2) const
{
    return Euclidean_distance(*obj1, *obj2);
}

bool GameObject::operator<(const GameObject &gameObject)
{
    return ID < gameObject.ID;
}
ostream &operator<<(ostream &out, const GameObject &gameObj)
{
    out << "ID_" << gameObj.ID;
    return out;
}