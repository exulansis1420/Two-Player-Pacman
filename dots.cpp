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
#include <string>

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

}
