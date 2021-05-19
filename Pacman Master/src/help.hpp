#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "pacman.hpp"

class Help
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event input;
    TTF_Font* font, *font2, *font2_small;
    Mix_Chunk *interim;
    bool intro_played;
    
    SDL_Color yellow,white,red ;
    SDL_Surface *title_s, *rules_s, *controls_s, *up_s, *down_s, *right_s, *left_s;
    SDL_Texture *title_t, *rules_t, *controls_t, *up_t, *down_t, *right_t, *left_t;

  
public:
    Help();
    std::string newwindow;
    void init();
    void kill();
    void loop();
};
