#include "pacman.hpp"

PacMan::PacMan() : Entity(285,475,30,30)
{
    eatenDots = 0;
    dir = 0;
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
    
    if(dir==1) {Entity::move(0,-1);}
    else if(dir==2){Entity::move(1,0);}
    else if(dir==3){Entity::move(-1,0);}
    else if(dir==4){Entity::move(0,1);}
        
        //screenPosY.;
}

void PacMan::move(SDL_Event input, SDL_Rect &textureRect, int &animstartframe)
{
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

        if(keys[SDL_SCANCODE_UP]) {
            dir=1;
        }
        else if(keys[SDL_SCANCODE_DOWN]) {
            dir=4;
        }
        else if(keys[SDL_SCANCODE_LEFT]) {
            dir=3;
        }
        else if(keys[SDL_SCANCODE_RIGHT]) {
            dir=2;
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
