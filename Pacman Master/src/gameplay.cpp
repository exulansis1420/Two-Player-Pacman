#include "gameplay.hpp"
#include "mazeimage.h"



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
    
    SDL_Surface* text_surf2=NULL;
    SDL_Texture* text2=NULL;
    
    SDL_Surface* text_surf3 = TTF_RenderText_Solid(font3, "lives:", {255,255,255});
    SDL_Texture* text3 = SDL_CreateTextureFromSurface(renderer, text_surf3);
    
    SDL_Texture* newTexture = NULL;
    std::string path = "resources/Images/dotspritesheet.png";
    SDL_Surface* loadedSurface = IMG_Load("/resources/Images/dotspritesheet.png");
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    
    dotloadMedia();

//    initt();
//    loadMedia2();
//    close();
    

    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT)
            {
                newwindow = "quit"; 
                quit = true;
            }
        }
        
//        if(character==0)
//        {
//            pacman.move(m,textureRect,animstartframe);
//
//
//        }
//        else {
//            ghost.move(m,textureRect2,animstartframe);
//        }
        
        
        pacmanRect = pacman.getEntRect();
        ghostRect = ghost.getEntRect();
        
        pacman.move(m,textureRect,animstartframe);
        ghost.move(m,textureRect2,animstartframe);
        
        
        
        float a = pacmanRect.x+15;
        float b = pacmanRect.y+15;
        
        float c = ghostRect.x+15;
        float d = ghostRect.y+15;
        
        int y = (a-10)/30;
        int x = (b-10)/30;
        
        if(m.dotmaze[x][y]==1 ) {
            pacman.eatDot(x,y,m);
        }
        else if (m.dotmaze[x][y]==2) {
            pacman.eatPDot(x,y,m);
            ghost.dead=true;
            ghost.five_start = SDL_GetTicks();
        }
        
        int scoree = 10 * pacman.getDotsEaten() + 50 * pacman.getPDotsEaten();
        std::string s = std::to_string(scoree);
        const char * cc = s.c_str();
        
        text_surf2 = TTF_RenderText_Solid(font3, cc, {255,255,0});
        text2 = SDL_CreateTextureFromSurface(renderer, text_surf2);
        
        
        
        float dist = pow(pow(a-c, 2) + pow(b-d,2), 0.5);
        
        if(dist<20) {
            
            if(ghost.dead==false)
            {
                pacman.reset(m);
                ghost.reset(m);
            }
            
            else if(ghost.dead==true)
            {
                pacman.reset2(m);
                ghost.dead=false;
                ghost.reset(m);
                

            }
        }
        
        int lives=pacman.lives;
        
        if(lives==0) {
            winner=1;
            quit=true;
        }
        
        if(m.totaldot==pacman.getDotsEaten()) {
            winner=0;
            quit=true;
        }
        
       // cout<<pacman.getDotsEaten()<<" "<<m.totaldot<<endl;
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        src.x=10;
        src.y=10;
        src.w=570;
        src.h=630;
        SDL_RenderCopy(renderer, BG, NULL, &src);
        displayDots(m.dots,newTexture,renderer);
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
        
        SDL_FreeSurface(text_surf2);
        SDL_DestroyTexture(text2);


        dest.x = 330;
        dest.y = 670;
        dest.w = text_surf3->w;
        dest.h = text_surf3->h;
        SDL_RenderCopy(renderer, text3, NULL, &dest);


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
    
   // SDL_FreeSurface(text_surf2);
    SDL_DestroyTexture( text2 );
    text_surf2=NULL;
    text2=NULL;
    
    SDL_FreeSurface(text_surf3);
    SDL_DestroyTexture( text3 );
    text_surf3=NULL;
    text3=NULL;
    
    SDL_FreeSurface(loadedSurface);
    SDL_DestroyTexture( newTexture );
    
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
    temp2 = IMG_Load("resources/Images/map.png");
    temp3 = IMG_Load("resources/Images/pacman.png");
    
    font3 = TTF_OpenFont("resources/Fonts/maneaterbb_bold.ttf",30);
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
    Mix_CloseAudio();

    //close1();
    IMG_Quit();
    SDL_Quit();
}

