#ifndef DOTS_H
#define DOTS_H

#include <stdio.h>
#include <iostream>
//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <vector>


std::vector<int> populate(std::vector<int> maze, int rows, int cols);
int eatDot(std::vector<int> &dots, int row, int col);
int displayDots(std::vector<int> dots, SDL_Renderer* &R);
bool dotloadMedia();

#endif

