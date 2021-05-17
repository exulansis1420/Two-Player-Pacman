#pragma once

#include "Entity.hpp"
#include "map.hpp"

class PacMan
    : public Entity
{
private:
    int eatenDots;
    bool dead;
    int dir;
    

public:
    PacMan();
    PacMan(std::pair<int,int> spawnPos);
    void move(Map &m, SDL_Rect &textureRect, int &animstartframe);
    void stop();
    void eatDot();
    void spawn(SDL_Rect &textureRect);
    void animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m);
    void eatPowerDot();
    int getDotsEaten();
    void setDead(bool d);
    bool isDead();
};
