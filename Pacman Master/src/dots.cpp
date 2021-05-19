#include "grid.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "cell.h"
#include "mazeimage.h"
//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "dots.h"
#include <string>


//Screen dimension constants
//const int SCREEN_WIDTH = 590;
//const int SCREEN_HEIGHT = 650;

std::vector<int> populate(std::vector<int> maze, int rows, int cols)
{
    std::vector<int> dots;
    //all 0 cells need to be given value 1 - small coin or 2 - large coin, except near spawn, range of 2
    //Exactly 8 big coins need to be there
    int cr, cc;
    for(int i=0; i< rows*cols; i++)
    {
        cr = i/cols;
        cc = i%cols;
        if (maze[i]!=0)
            dots.push_back(0);
        else{
            dots.push_back(1);
            if((cr-11)*(cr-11) < 4 && ((cc-5)*(cc-5) < 4 || (cc-15)*(cc-15) < 4))
                dots[i]=0;
        }
    }
    //Big coins
    dots[5*19+1]=2;
    dots[5*19+17]=2;
    dots[15*19+1]=2;
    dots[15*19+17]=2;
    //Print Test
    /*for(int i=0; i<21; i++){
        for(int j=0; j<19; j++){
            std::cout<<dots[i*19+j];
        }
        std::cout<<std::endl;
    }*/
    return dots;
}

int eatDot(std::vector<int> &dots, int row, int col)
{
    switch(dots[row*19+col]){
        case 0: return -1;
                break;
        case 1: dots[row*19+col] = 0; return 1;
                break;
        case 2: dots[row*19+col] = 0; return 2;
                break;
    }
    return 0;

}

//Loads media
bool dotloadMedia();


//Scene sprites
SDL_Rect dotgSpriteClips[2];


int tileType2 (std::vector<int> dots, int i)
{
    switch(dots[i]){
        case 0 : return -1;
        case 1:  return 1;
        case 2: return 0;
    }
    return 0;
}

bool dotloadMedia()
{
    for(int i = 0; i<2;i++){
        dotgSpriteClips[i].x = i*30;
        dotgSpriteClips[i].y =    0;
        dotgSpriteClips[i].w =   30;
        dotgSpriteClips[i].h =   30;
    }
    return true;
}

/*SDL_Texture* newTexture = NULL;
std::string path = "/Users/tanishq/Downloads/dotspritesheet.png"
SDL_Surface* loadedSurface = IMG_Load(path.c_str());
newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
*/

int displayDots(std::vector<int> dots, SDL_Texture* mTexture, SDL_Renderer* &R)
{
    int r,c;
    for(int i=0; i<dots.size(); i++)
    {
        r = i/19; c = i % 19;
        if(dots[i]==0)
            continue;
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { dotgSpriteClips[0].w*c + 10, dotgSpriteClips[0].h*r + 10, 60, 30 };
        //Set clip rendering dimensions
        SDL_Rect* clip = &dotgSpriteClips[tileType2(dots,i)];
        if( clip != NULL ){
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        //Render to screen
        SDL_RenderCopy( R, mTexture, clip, &renderQuad );
    }
    return 0;
}
