#include "gameplay.hpp"


using namespace std;

Gameplay::Gameplay() {
    quit = false;
    BG = NULL;
    spriteSheet = NULL;
    animstartframe=0;
}

void Gameplay::loop() {
    
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

}

void Gameplay::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Pacman 1.0", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    temp2 = IMG_Load("/Users/tanishq/Desktop/SDL Tutorial/SDL Tutorial/maze1.png");
    BG = SDL_CreateTextureFromSurface(renderer, temp2);
    pacman.setimage(spriteSheet, textureRect, renderer);
    pacmanRect = pacman.getEntRect();
}

void Gameplay::kill() {
    
    SDL_FreeSurface(temp2);
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(BG);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

