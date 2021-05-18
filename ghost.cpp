#include "ghost.hpp"
#include<iostream>

Ghost::Ghost() : Entity() {
    //
}

Ghost::Ghost(std::pair<int,int> spawnPos) : Entity()
{
    Entity::tileX = spawnPos.second;
    Entity::tileY = spawnPos.first;
    Entity::screenPosX = 10+30*spawnPos.second;
    Entity::screenPosY = 10+30*spawnPos.first;
    Entity::width =30;
    Entity::height =30;
    
    Entity::entRect.x = 10+30*spawnPos.second;
    Entity::entRect.y = 10+30*spawnPos.first;
    Entity::entRect.w = 30;
    Entity::entRect.h = 30;

  
    dir = 0;
}
void Ghost::animate(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m) {
    //0 = DEFAULT //1 = UP, 2 = RIGHT, 3 = LEFT, 4 = DOWN
   
        if(direction ==0) {
            //no direction change
        }
        else if(direction ==1) {
            animstartframe = 0;
            
        }
        else if(direction==2) {
            
            animstartframe = 90;
        }
        else if(direction==3){
            
            animstartframe = 60;
        }
        else{

            animstartframe = 30;
        }
        int totalFrames = 2;
        int delayPerFrame = 100;
        
        int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
        textureRect.y = 15;
        textureRect.x = animstartframe + frame * textureRect.w;

    int currx = m.getPMpos().first;
    int curry = m.getPMpos().second;
    int check =-1;
    if(direction==1) {
        check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else {Entity::move(0,-2);}
        curry = (Entity::screenPosX + Entity::width/2-10) /30;
        currx = (Entity::screenPosY-10 ) /30;
    }
    
    else if(direction==2){
        check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else if(screenPosX>590) {
            Entity::screenPosX=0;
            Entity::entRect.x=0;
        }
        else {Entity::move(2,0);}
        curry = (Entity::screenPosX + Entity::width -10 ) /30;
        currx = (Entity::screenPosY + Entity::height/2 -10) /30;
    }
    else if(direction==3){
        check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else if(screenPosX<0) {
            Entity::screenPosX=590;
            Entity::entRect.x=590;
        }
        else {Entity::move(-2,0);}
        curry = (Entity::screenPosX  -10) /30;
        currx = (Entity::screenPosY + Entity::height/2 -10) /30;
    }
    else if(direction==4){
         check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else {Entity::move(0,2);}
        curry = (Entity::screenPosX + Entity::width/2 -10 ) /30;
        currx = (Entity::screenPosY + Entity::height -10 ) /30;
    }
    
    
    m.updatePMpos({currx,curry});
   std::cout<<currx<<" "<<curry<<" "<<Entity::screenPosX<<" "<<Entity::screenPosY<<std::endl;
    
        //screenPosY.;
}

void Ghost::move(Map &m, SDL_Rect &textureRect, int &animstartframe)
{
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    int currx = m.getPMpos().first;
    int curry = m.getPMpos().second;
    int check =-1;
    //std::cout<<m.maze[currx][curry];

        if(keys[SDL_SCANCODE_UP]) {
            check= m.maze[currx][curry-1];
            {dir=1;}
        }
        else if(keys[SDL_SCANCODE_DOWN]) {
            check= m.maze[currx][curry+1];
            
             {dir=4;}
        }
        else if(keys[SDL_SCANCODE_LEFT]) {
    
            check= m.maze[currx-1][curry];
            
            {dir=3;}
        }
        else if(keys[SDL_SCANCODE_RIGHT]) {

            check= m.maze[currx+1][curry];
            
            {dir=2;}
        }

    animate(textureRect,dir,animstartframe,m);
}





