#include "gameplay.hpp"


using namespace std;

Gameplay::Gameplay() {
    quit = false;
    BG = NULL;
    spriteSheet = NULL;
    animstartframe=0;
}

void Gameplay::loop() {
    
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Surface* text_surf;
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

        src.x=0;
        src.y=0;
        src.w=600;
        src.h=640;
        SDL_RenderCopy(renderer, BG, NULL, &src);
        SDL_RenderCopy(renderer, spriteSheet, &textureRect, &pacmanRect);
        
        text_surf = TTF_RenderText_Solid(font3, "score:", {255,255,255});
        text = SDL_CreateTextureFromSurface(renderer, text_surf);
        dest.x = 50;
        dest.y = 650;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, text, NULL, &dest);
        
        text_surf = TTF_RenderText_Solid(font3, "0000", {255,255,0});
        text = SDL_CreateTextureFromSurface(renderer, text_surf);
        dest.x = 175;
        dest.y = 650;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, text, NULL, &dest);
        
        text_surf = TTF_RenderText_Solid(font3, "lives:", {255,255,255});
        text = SDL_CreateTextureFromSurface(renderer, text_surf);
        dest.x = 340;
        dest.y = 650;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, text, NULL, &dest);
        
        SDL_FreeSurface(text_surf);
        text_surf = NULL;

        int lives=3;
        src.x=445;
        src.y=650;
        src.w=35;
        src.h=30;
        for(int i=0;i<lives;i++)
        {
            SDL_RenderCopy(renderer, PM, NULL, &src);
            src.x+=30;
        }
                        
        
        SDL_RenderPresent(renderer);
        
    }

}

void Gameplay::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    
    window = SDL_CreateWindow("Pacman 1.0", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 600, 700, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    temp2 = IMG_Load("/Users/tanishq/Desktop/SDL Tutorial/SDL Tutorial/maze1.png");
    temp3 = IMG_Load("/Users/tanishq/Downloads/pacman.png");
    
    font3 = TTF_OpenFont("/Users/tanishq/Downloads/maneaterbb_bold.ttf",30);
    BG = SDL_CreateTextureFromSurface(renderer, temp2);
    PM = SDL_CreateTextureFromSurface(renderer, temp3);
    pacman.setimage(spriteSheet, textureRect, renderer);
    pacmanRect = pacman.getEntRect();
}

void Gameplay::kill() {
    
    SDL_FreeSurface(temp2);
    SDL_FreeSurface(temp3);
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(BG);
    SDL_DestroyTexture(PM);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture( text );
    text = NULL;
    IMG_Quit();
    SDL_Quit();
}

