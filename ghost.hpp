#pragma once

#include "Entity.hpp"
#include "map.hpp"

class Ghost
    : public Entity
{
private:
    bool dead;
    int dir;
    

public:
    Ghost();
    Ghost(std::pair<int,int> spawnPos);
    void move(Map &m, SDL_Rect &textureRect, int &animstartframe);

    void animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m);

    void setDead(bool d);
    bool isDead();
};

