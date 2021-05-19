#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pacman.hpp"

class About
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event input;
    TTF_Font* font, *font2, *font2_small;
    Mix_Chunk *interim;
    bool intro_played;
    
    SDL_Color yellow,white,red ;
    SDL_Surface *title_s, *one_surf, *two_surf, *title2_s;
    SDL_Texture *title_t, *one_text, *two_text, *title2_t ;

  
public:
    About();
    std::string newwindow;
    void init();
    void kill();
    void loop();
};
