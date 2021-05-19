#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Character
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture, *text, *arrowSheet, *bigpac, *bigghost;
    TTF_Font* font, *font2, *font2_small;
    Mix_Chunk *menuchange , *intro , *interim;
    std::string ee;
    SDL_Event e;
    int ax,ay;
    bool intro_played;
    SDL_Event input;
    
    
    SDL_Color yellow,white,red ;
    SDL_Surface *title_surf, *continue_surf, *empty_surf, *temp, *name1_surf, *name2_surf;
    SDL_Texture *title_text, *continue_text, *empty_text, *name1_text, *name2_text;

public:
    std::string newwindow;
    int charInt;
    Character();
    void init();
    void kill();
    void loop();
};
