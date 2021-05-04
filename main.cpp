#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "pacman.hpp"

int main(int argc, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Pacman 1.0", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event input;
    bool quit = false;

    
    SDL_Texture* BG = NULL;
    SDL_Surface* temp2 = IMG_Load("/Users/tanishq/Desktop/SDL Tutorial/SDL Tutorial/maze1.png");
    BG = SDL_CreateTextureFromSurface(renderer, temp2);
    SDL_FreeSurface(temp2);

    
    PacMan pacman;
    SDL_Texture* spriteSheet = NULL;
    SDL_Rect textureRect;
    pacman.setimage(spriteSheet, textureRect, renderer);
    
    SDL_Rect pacmanRect = pacman.getEntRect();
    int animstartframe=0;
    
    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;
        }
        
        pacman.move(input,textureRect,animstartframe);
        pacmanRect = pacman.getEntRect();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_RenderCopy(renderer, BG, NULL, NULL);
        SDL_RenderCopy(renderer, spriteSheet, &textureRect, &pacmanRect);
        
        SDL_RenderPresent(renderer);
        
    }
    
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

