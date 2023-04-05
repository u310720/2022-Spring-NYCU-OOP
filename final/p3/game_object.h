#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <iostream>

class GameObject
{
private:
    static GameObject *gameMap[100][100];
    static int ID_count;

    void disappear_from_the_map();

protected:
    int ID, HP;
    int x, y;

public:
    GameObject();
    GameObject(int x, int y);
    ~GameObject();

    bool is_available_at(int x, int y) const;
    void go_occupy(int x, int y);
    void go_away_from(int x, int y);

    double Euclidean_distance(const GameObject &obj1, const GameObject &obj2) const;
    double Euclidean_distance(const GameObject *obj1, const GameObject *obj2) const;

    friend std::ostream &operator<<(std::ostream &, const GameObject &);
    virtual bool operator<(const GameObject &);
};

#endif // __GAME_OBJECT_H__