#include "pacman.hpp"

PacMan::PacMan() : Entity(285,475,30,30)
{
    eatenDots = 0;
}
void PacMan::animate(SDL_Rect &textureRect, int direction, int &animstartframe) {
    //0 = DEFAULT //1 = UP, 2 = RIGHT, 3 = LEFT, 4 = DOWN
    if(direction ==0) {
        //no direction change
    }
    else if(direction ==1) {
        animstartframe = 0;
    }
    else if(direction==2) {
        animstartframe = 135;
    }
    else if(direction==3){
        animstartframe = 90;
    }
    else{
        animstartframe = 45;
    }
    int totalFrames = 3;
    int delayPerFrame = 100;
    
    int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
    textureRect.y = 0;
    textureRect.x = animstartframe + frame * textureRect.w;
    
}

void PacMan::move(SDL_Event input, SDL_Rect &textureRect, int &animstartframe)
{
    int dir=0;
    if(input.type == SDL_KEYDOWN)
    {
        if(input.key.keysym.sym == SDLK_UP) {
            Entity::move(0,-1);
            dir=1;
        }
        else if(input.key.keysym.sym == SDLK_DOWN) {
            Entity::move(0,1);
            dir=4;
        }
        else if(input.key.keysym.sym == SDLK_LEFT) {
            Entity::move(-1,0);
            dir=3;
        }
        else if(input.key.keysym.sym == SDLK_RIGHT) {
            Entity::move(1,0);
            dir=2;
        }
    }
    
    animate(textureRect,dir,animstartframe);
   
}


void PacMan::eatDot()
{
    eatenDots++;
}

int PacMan::getDotsEaten()
{
    return eatenDots;
}

void PacMan::setDead(bool d)
{
    dead = d;
}

bool PacMan::isDead()
{
    return dead;
}
