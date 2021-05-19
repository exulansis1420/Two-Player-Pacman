#pragma once

#include "Entity.hpp"
#include "map.hpp"
#include <SDL2/SDL_mixer.h>

class PacMan
    : public Entity
{
private:
    int eatenDots;
    int eatenPDots;
    bool dead;
    int dir;

    

public:
    PacMan();
    PacMan(std::pair<int,int> spawnPos);
    void move(Map &m, SDL_Rect &textureRect, int &animstartframe);
    int lives;
    void stop(int dir, SDL_Rect &textureRect, Map &m);
    void eatDot(int x, int y, Map &m);
    void spawn(SDL_Rect &textureRect);
    void animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m);
    void eatPDot(int x, int y, Map &m);
    int getDotsEaten();
    int getPDotsEaten();
    void setDead(bool d);
    bool isDead();
    void reset(Map &m);
    void reset2(Map &m);
};
