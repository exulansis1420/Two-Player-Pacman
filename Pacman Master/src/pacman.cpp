#include "pacman.hpp"
#include<iostream>

PacMan::PacMan() : Entity() {
    //
}

PacMan::PacMan(std::pair<int,int> spawnPos) : Entity()
{
    Entity::tileX = spawnPos.second;
    Entity::tileY = spawnPos.first;
    Entity::screenPosX = 10+30*spawnPos.second;
    Entity::screenPosY = 10+30*spawnPos.first;
    Entity::width =32;
    Entity::height =32;
    
    Entity::entRect.x = 10+30*spawnPos.second;
    Entity::entRect.y = 10+30*spawnPos.first;
    Entity::entRect.w = 30;
    Entity::entRect.h = 30;
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    Entity::intro = Mix_LoadWAV( "resources/Sounds/pacman_beginning.wav" );
    Entity::dead = Mix_LoadWAV("resources/Souns/death_1.wav");
    Entity::munch = Mix_LoadWAV("resources/Sounds/munch_a.wav");
    Entity::fruit = Mix_LoadWAV("resources/Sounds/fruit.wav");
    Entity::eatghost = Mix_LoadWAV("resources/Sounds/ghost_eat_3.wav");
    Entity::five_start = 0;
    
  
    lives=3;
    
    eatenDots = 0;
    eatenPDots = 0;
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
    

       //std::cout<<currx<<" "<<curry<<" "<<Entity::screenPosX<<" "<<Entity::screenPosY<<std::endl;
    
        //screenPosY.;
}

void PacMan::move(Map &m, SDL_Rect &textureRect, int &animstartframe)
{
    
    if(Entity::play_intro==true)
    {
        
        Mix_PlayChannel( 1, Entity::intro, 0 );
        Entity::play_intro=false;
    }

    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    int currx = m.getPMpos().first;
    int curry = m.getPMpos().second;
    int check =-1;
    //std::cout<<m.maze[currx][curry];
    if(Mix_Playing(1)!=1 )
    {
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
    
}

void PacMan::reset(Map &m) {
    Mix_PlayChannel(3,Entity::dead,0);
    while(Mix_Playing(3)==1){
        
    }
    Entity::play_intro=true;
    m.updatePMpos(m.getPMspawn());
    m.updateGpos(m.getGspawn());
    Entity::screenPosX= 10+30*m.getPMspawn().second;
    Entity::screenPosY= 10+30*m.getPMspawn().first;
    Entity::entRect.x = Entity::screenPosX;
    Entity::entRect.y = Entity::screenPosY;
    lives=lives-1;
}

void PacMan::reset2(Map &m) {
    Mix_PlayChannel(3,Entity::eatghost,0);
    while(Mix_Playing(3)==1){
        
    }
   
    Entity::play_intro=true;
    m.updatePMpos(m.getPMspawn());
    m.updateGpos(m.getGspawn());
    Entity::screenPosX= 10+30*m.getPMspawn().second;
    Entity::screenPosY= 10+30*m.getPMspawn().first;
    Entity::entRect.x = Entity::screenPosX;
    Entity::entRect.y = Entity::screenPosY;
    lives=lives+1;
}


void PacMan::eatDot(int x, int y, Map &m)
{
    eatenDots++;
    m.dotmaze[x][y] =0;
    m.dots[19*x+y]=0;
    Mix_PlayChannel(-1,Entity::munch,0);
    
}

void PacMan::eatPDot(int x, int y, Map &m)
{
    eatenDots++;
    eatenPDots++; 
    m.dotmaze[x][y] =0;
    m.dots[19*x+y]=0;
    Mix_PlayChannel(3,Entity::fruit,0);
    while(Mix_Playing(3)==1){
        
    }
  
}

int PacMan::getDotsEaten()
{
    return eatenDots;
}

int PacMan::getPDotsEaten()
{
    return eatenPDots;
}

void PacMan::setDead(bool d)
{
    dead = d;
}

bool PacMan::isDead()
{
    return dead;
}
