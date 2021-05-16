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
    SDL_Texture *texture, *text;
    TTF_Font* font, *font2;
    Mix_Chunk *menuchange , *intro , *interim;
    std::string ee;
    SDL_Event e;
    int ax,ay;
    bool intro_played;

public:
    std::string newwindow;
    Menu();
    bool init();
    void kill();
    bool loop();
};
