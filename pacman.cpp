#include "pacman.hpp"
#include<iostream>

PacMan::PacMan() : Entity() {
    //
}

PacMan::PacMan(std::pair<int,int> spawnPos) : Entity()
{
    Entity::tileX = spawnPos.first;
    Entity::tileY = spawnPos.second;
    Entity::screenPosX = 20*spawnPos.first;
    Entity::screenPosY = 20*spawnPos.second;
    Entity::width =20;
    Entity::height =20;
    
    Entity::entRect.x = 20*spawnPos.first;
    Entity::entRect.y = 20*spawnPos.second;
    Entity::entRect.w = 20;
    Entity::entRect.h = 20;

    eatenDots = 0;
    dir = 0;
}
void PacMan::animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m) {
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

    int currx = m.getPMpos().first;
    int curry = m.getPMpos().second;
    int check =-1;
    if(dir==1) {
        check= m.maze[currx][curry-1];
        if(check!=1) {Entity::move(0,-1);}
    }
    
    else if(dir==2){
        int check= m.maze[currx+1][curry];
        if(check!=1) {Entity::move(1,0);}
    }
    else if(dir==3){
        int check= m.maze[currx-1][curry];
        if(check!=1) {Entity::move(-1,0);}
    }
    else if(dir==4){
        int check= m.maze[currx][curry+1];
        if(check!=1) {Entity::move(0,1);}
    }
    
    std::cout<<currx<<" "<<curry<<std::endl;
    currx = Entity::screenPosX/20;
    curry = Entity::screenPosY/20;
    m.updatePMpos({currx,curry});
    
        //screenPosY.;
}

void PacMan::move(Map &m, SDL_Rect &textureRect, int &animstartframe)
{
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    int currx = m.getPMpos().first;
    int curry = m.getPMpos().second;
    int check =-1;
    //std::cout<<m.maze[currx][curry];

        if(keys[SDL_SCANCODE_UP]) {
            check= m.maze[currx][curry-1];
            if(check!=1) {dir=1;}
        }
        else if(keys[SDL_SCANCODE_DOWN]) {
            check= m.maze[currx][curry+1];
            
            if(check!=1) {dir=4;}
        }
        else if(keys[SDL_SCANCODE_LEFT]) {
    
            check= m.maze[currx-1][curry];
            
            if(check!=1) {dir=3;}
        }
        else if(keys[SDL_SCANCODE_RIGHT]) {

            check= m.maze[currx+1][curry];
            
            if(check!=1) {dir=2;}
        }

    animate(textureRect,dir,animstartframe,m);
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
