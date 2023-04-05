#include "barracks.h"

Barracks::Barracks(int x, int y, int property, Player &player) : player(player)
{
    HP = 300;
    laborers[0] = nullptr;
    laborers[1] = nullptr;
    this->property = property;
    player.food -= 300; // cost 300 player's food
}
Barracks::~Barracks()
{
    all_laborers_dead();
}
void Barracks::all_laborers_dead()
{
    if (laborers[0])
    {
        delete laborers[0];
        laborers[0] = nullptr;
    }
    if (laborers[1])
    {
        delete laborers[1];
        laborers[1] = nullptr;
    }
}

bool Barracks::can_generate_a_soldier() const
{
    if (player.food < 300)
        return false;

    if (!is_available_at(x, y + 1))
        return false;

    int nLaborers = 0;
    if (laborers[0] != nullptr)
        ++nLaborers;
    if (laborers[1] != nullptr)
        ++nLaborers;

    return nLaborers == 2;
}
void Barracks::generate_a_soldier()
{
    player.food -= 300;

    Soldier *soldier = new Soldier(x, y + 1);
    switch (property)
    {
    case ARCHER_BARRACKS:
        soldier->being_archer();
        break;
    case CAVALRY_BARRACKS:
        soldier->being_cavalry();
        break;
    case SPEARMAN_BARRACKS:
        soldier->being_spearman();
        break;

    default:
        break;
    }
}