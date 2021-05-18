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
   
    SDL_Surface* text_surf1 = TTF_RenderText_Solid(font3, "score:", {255,255,255});
    SDL_Texture* text1 = SDL_CreateTextureFromSurface(renderer, text_surf1);
    
    SDL_Surface* text_surf2 = TTF_RenderText_Solid(font3, "0000", {255,255,0});
    SDL_Texture* text2 = SDL_CreateTextureFromSurface(renderer, text_surf2);
    
    SDL_Surface* text_surf3 = TTF_RenderText_Solid(font3, "lives:", {255,255,255});
    SDL_Texture* text3 = SDL_CreateTextureFromSurface(renderer, text_surf3);
    
    
    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;
        }
        
        if(character==0)
        {
            pacman.move(m,textureRect,animstartframe);

            
        }
        else {
            ghost.move(m,textureRect2,animstartframe);
        }
        pacmanRect = pacman.getEntRect();
        ghostRect = ghost.getEntRect();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        src.x=10;
        src.y=10;
        src.w=570;
        src.h=630;
        SDL_RenderCopy(renderer, BG, NULL, &src);
        SDL_RenderCopy(renderer, spriteSheet, &textureRect, &pacmanRect);
        SDL_RenderCopy(renderer, spriteSheet, &textureRect2, &ghostRect);
        
        
        dest.x = 40;
        dest.y = 670;
        dest.w = text_surf1->w;
        dest.h = text_surf1->h;
        SDL_RenderCopy(renderer, text1, NULL, &dest);

        
        dest.x = 165;
        dest.y = 670;
        dest.w = text_surf2->w;
        dest.h = text_surf2->h;
        SDL_RenderCopy(renderer, text2, NULL, &dest);


        dest.x = 330;
        dest.y = 670;
        dest.w = text_surf3->w;
        dest.h = text_surf3->h;
        SDL_RenderCopy(renderer, text3, NULL, &dest);

       

        int lives=3;
        src.x=435;
        src.y=670;
        src.w=35;
        src.h=30;
        for(int i=0;i<lives;i++)
        {
            SDL_RenderCopy(renderer, PM, NULL, &src);
            src.x+=30;
        }

        
        SDL_RenderPresent(renderer);
        
    }
    
    SDL_FreeSurface(text_surf1);
    SDL_DestroyTexture( text1 );
    text_surf1=NULL;
    text1=NULL;
    
    SDL_FreeSurface(text_surf2);
    SDL_DestroyTexture( text2 );
    text_surf2=NULL;
    text2=NULL;
    
    SDL_FreeSurface(text_surf3);
    SDL_DestroyTexture( text3 );
    text_surf3=NULL;
    text3=NULL;
    
}

void Gameplay::init(int c) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    
    m.init();
    
    character =c;
    
    window = SDL_CreateWindow("Pacman 1.0", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, 590, 740, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    temp2 = IMG_Load("/Users/tanishq/Desktop/SDL Tutorial copy/SDL Tutorial/map.png");
    temp3 = IMG_Load("/Users/tanishq/Downloads/pacman.png");
    
    font3 = TTF_OpenFont("/Users/tanishq/Downloads/maneaterbb_bold.ttf",30);
    BG = SDL_CreateTextureFromSurface(renderer, temp2);
    PM = SDL_CreateTextureFromSurface(renderer, temp3);
    
  
    pacman= PacMan(m.getPMspawn());
    pacman.setimage(spriteSheet, textureRect, renderer,0);
    pacmanRect = pacman.getEntRect();
    
    ghost= Ghost(m.getGspawn());
    ghost.setimage(spriteSheet, textureRect2, renderer,1);
    ghostRect = ghost.getEntRect();
}

void Gameplay::kill() {
    
    SDL_FreeSurface(temp2);
    SDL_FreeSurface(temp3);
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(BG);
    SDL_DestroyTexture(PM);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

