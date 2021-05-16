#pragma once

#include "Entity.hpp"

class PacMan
    : public Entity
{
private:
    int eatenDots;
    bool dead;
    int dir;
    

public:
    PacMan();
    void move(SDL_Event input, SDL_Rect &textureRect, int &animstartframe);
    void stop();
    void eatDot();
    void spawn(SDL_Rect &textureRect);
    void animate(SDL_Rect &textureRect, int direction, int &animstartframe);
    void eatPowerDot();
    int getDotsEaten();
    void setDead(bool d);
    bool isDead();
};
