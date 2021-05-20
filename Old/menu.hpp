#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Menu
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture *texture, *text, *arrowSheet;
    TTF_Font* font, *font2, *font2_small;
    Mix_Chunk *menuchange , *intro , *interim;
    std::string ee;
    SDL_Event e;
    int ax,ay;
    bool intro_played;
    
    SDL_Color yellow,white,red ;
    SDL_Surface *pacman_surf, *start_surf, *help_surf, *about_surf, *continue_surf, *empty_surf, *temp;
    SDL_Texture *pacman_text, *start_text, *help_text, *about_text, *continue_text, *empty_text;

public:
    std::string newwindow;
    Menu();
    bool init();
    void kill();
    bool loop();
};
