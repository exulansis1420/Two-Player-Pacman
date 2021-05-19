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
    Entity::siren = Mix_LoadWAV( "resources/Sounds/siren_slow.wav" );
    Entity::largepel = Mix_LoadWAV("resources/Sounds/large_pellet_loop.wav");

  
    dir = 0;
    dead=false;
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

    int currx = m.getGpos().first;
    int curry = m.getGpos().second;
    int check =-1;
    if(direction==1) {
        check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else {Entity::move(0,-2.0);}
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
    
    if(Mix_Playing(2)!=1)
    {
        if(dead==false)
        {
            Mix_PlayChannel( 2, Entity::siren, 0 );
        }
        else {
            Mix_PlayChannel( 2, Entity::largepel, 0 );
        }
    }
    

    
    m.updateGpos({currx,curry});
   //std::cout<<currx<<" "<<curry<<" "<<Entity::screenPosX<<" "<<Entity::screenPosY<<std::endl;
    
        //screenPosY.;
}

void Ghost::animate2(SDL_Rect &textureRect, int direction, int &animstartframe, Map &m) {
    //0 = DEFAULT //1 = UP, 2 = RIGHT, 3 = LEFT, 4 = DOWN
   

        int totalFrames = 3;
        int delayPerFrame = 100;
        
        int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
        textureRect.y = 15;
        textureRect.x = 120 + frame * textureRect.w;

    int currx = m.getGpos().first;
    int curry = m.getGpos().second;
    int check =-1;
    if(direction==1) {
        check= m.maze[currx][curry];
        if(check==1) {
            
        }
        else {Entity::move(0,-2.0);}
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
    
    if(Mix_Playing(2)!=1)
    {
        if(dead==false)
        {
            Mix_PlayChannel( 2, Entity::siren, 0 );
        }
        else {
            Mix_PlayChannel( 2, Entity::largepel, 0 );
        }
    }
    
    
    
    m.updateGpos({currx,curry});
   // cou(SDL_GetTicks()-five_start)>5000
   // std::cout<<(SDL_GetTicks()-Entity::five_start)<<std::endl;
    if( (SDL_GetTicks()-five_start)>5000) {
        dead=false;
    }
   //std::cout<<currx<<" "<<curry<<" "<<Entity::screenPosX<<" "<<Entity::screenPosY<<std::endl;
    
        //screenPosY.;
}

void Ghost::move(Map &m, SDL_Rect &textureRect, int &animstartframe)
{
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(Mix_Playing(1)!=1 )
    {
        int currx = m.getGpos().first;
        int curry = m.getGpos().second;
        int check =-1;
    //std::cout<<m.maze[currx][curry];

        if(keys[SDL_SCANCODE_W]) {
            check= m.maze[currx][curry-1];
            {dir=1;}
        }
        else if(keys[SDL_SCANCODE_S]) {
            check= m.maze[currx][curry+1];
            
             {dir=4;}
        }
        else if(keys[SDL_SCANCODE_A]) {
    
            check= m.maze[currx-1][curry];
            
            {dir=3;}
        }
        else if(keys[SDL_SCANCODE_D]) {

            check= m.maze[currx+1][curry];
            
            {dir=2;}
        }
        
    if(dead==false)
    {
        animate(textureRect,dir,animstartframe,m);
    }
    
    else {
        
        animate2(textureRect,dir,animstartframe,m);
    }
        
    }
}

void Ghost::reset(Map &m) {
    Entity::play_intro=true;
    m.updatePMpos(m.getGspawn());
    m.updateGpos(m.getGspawn());
    Entity::screenPosX= 10+30*m.getGspawn().second;
    Entity::screenPosY= 10+30*m.getGspawn().first;
    Entity::entRect.x = Entity::screenPosX;
    Entity::entRect.y = Entity::screenPosY;
}



