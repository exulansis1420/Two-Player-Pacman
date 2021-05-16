#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pacman.hpp"

class Gameplay
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event input;
    SDL_Texture *text;
    TTF_Font *font3, *font4;
    bool quit;
    SDL_Texture* BG, *PM;
    PacMan pacman;
    SDL_Texture* spriteSheet;
    SDL_Surface* temp2, *temp3;
    SDL_Rect textureRect;
    SDL_Rect pacmanRect;
    int animstartframe;

public:
    Gameplay();
    void init();
    void kill();
    void loop();
};
