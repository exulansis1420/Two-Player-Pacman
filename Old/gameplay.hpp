#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pacman.hpp"
#include "map.hpp"
#include "ghost.hpp"
#include "dots.h"

class Gameplay
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event input;
    TTF_Font *font3, *font4;
    bool quit;
    SDL_Texture* BG, *PM;
    Map m;
    PacMan pacman;
    Ghost ghost;
    SDL_Texture* spriteSheet;
    SDL_Surface* temp2, *temp3;
    SDL_Rect textureRect, textureRect2;
    SDL_Rect pacmanRect;
    SDL_Rect ghostRect;
    int animstartframe;
    int character;
    
  

public:
    Gameplay();
    int winner;
    std::string newwindow;
    void init(int c);
    void kill();
    void loop();
};
