#pragma once

#include "Entity.hpp"
#include "map.hpp"

class Ghost
    : public Entity
{
private:
    int eatenDots;
    bool dead;
    int dir;
    

public:
    Ghost();
    Ghost(std::pair<int,int> spawnPos);
    void move(Map &m, SDL_Rect &textureRect, int &animstartframe);
    void stop(int dir, SDL_Rect &textureRect, Map &m);
    void eatDot();
    void spawn(SDL_Rect &textureRect);
    void animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m);
    void eatPowerDot();
    int getDotsEaten();
    void setDead(bool d);
    bool isDead();
};

