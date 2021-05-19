#include "about.hpp"

using namespace std;

About::About() {
    
    
}

void About::init() {
    SDL_Init( SDL_INIT_EVERYTHING );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    IMG_Init(IMG_INIT_PNG) ;
    TTF_Init();

    window = SDL_CreateWindow( "PacMan 1.0 - About", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );


    font = TTF_OpenFont("resources/Fonts/emulogic.ttf",60);
    font2 = TTF_OpenFont("resources/Fonts/emulogic.ttf",30);
    font2_small = TTF_OpenFont("resources/Fonts/emulogic.ttf",15);

    yellow = {255,231,55  };
    white = {255,255,255};
    red = {255,0,0};
    
   
    title_s = TTF_RenderText_Solid(font, "ABOUT", {0,255,0});
    title_t = SDL_CreateTextureFromSurface(renderer, title_s);
    
    title2_s = TTF_RenderText_Solid(font2, "DEVELOPERS", {255,0,0});
    title2_t = SDL_CreateTextureFromSurface(renderer, title2_s);

    one_surf = TTF_RenderText_Solid(font2_small, "TANISHQ DUBEY", yellow);
    one_text = SDL_CreateTextureFromSurface(renderer, one_surf);
    
   two_surf = TTF_RenderText_Solid(font2_small, "ANIKET MISHRA", yellow);
   two_text = SDL_CreateTextureFromSurface(renderer, two_surf);

    /*
    About_surf = TTF_RenderText_Solid(font2, "About", red);
    About_text = SDL_CreateTextureFromSurface(renderer, About_surf);

    about_surf = TTF_RenderText_Solid(font2, "about", red);
    about_text = SDL_CreateTextureFromSurface(renderer, about_surf);

    continue_surf = TTF_RenderText_Solid(font2_small, "press enter to continue", {0,0,255});
    continue_text = SDL_CreateTextureFromSurface(renderer, continue_surf);

    empty_surf = TTF_RenderText_Solid(font2_small, " ", {0,0,255});
    empty_text = SDL_CreateTextureFromSurface(renderer, empty_surf);*/
    
    
    interim = Mix_LoadWAV( "resources/Sounds/pacman_intermission.wav" );
    
}

    
void About::loop() {
    SDL_Rect dest;
    bool quit=false;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Surface* continue_surf = TTF_RenderText_Solid(font2_small, "press ESC to return", {0,0,255});
    SDL_Texture* continue_text = SDL_CreateTextureFromSurface(renderer, continue_surf);
    
    SDL_Surface* empty_surf = TTF_RenderText_Solid(font2_small, " ", {0,0,255});
    SDL_Texture* empty_text = SDL_CreateTextureFromSurface(renderer, empty_surf);
    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT)
            {
                newwindow="quit";
                quit = true;
            }
            
            if (keys[SDL_SCANCODE_ESCAPE]){
                newwindow="menu";
                quit=true;}
        }
         
       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        dest.x = 200;
        dest.y = 20;
        dest.w = title_s->w;
        dest.h = title_s->h;
        SDL_RenderCopy(renderer, title_t, NULL, &dest);
        
        dest.x = 30;
        dest.y = 150;
        dest.w = title2_s->w;
        dest.h = title2_s->h;
        SDL_RenderCopy(renderer, title2_t, NULL, &dest);
        
        dest.x = 30;
        dest.y = 250;
        dest.w = one_surf->w;
        dest.h = one_surf->h;
        SDL_RenderCopy(renderer, one_text, NULL, &dest);
        
        dest.x = 30;
        dest.y = 300;
        dest.w = two_surf->w;
        dest.h = two_surf->h;
        SDL_RenderCopy(renderer, two_text, NULL, &dest);
        
        
        
        int frame = (SDL_GetTicks() / 300) % 2;
        if(frame%2==1) {
            
            dest.x = 300 - (continue_surf->w / 2.0f);
            dest.y = 500;
            dest.w = continue_surf->w;
            dest.h = continue_surf->h;
              
            SDL_RenderCopy(renderer, continue_text, NULL, &dest);
            
        }
        else {
            
            dest.x = 300 - (empty_surf->w / 2.0f);
            dest.y = 500;
            dest.w = empty_surf->w;
            dest.h = empty_surf->h;
             
            SDL_RenderCopy(renderer, empty_text, NULL, &dest);
        }
        
        SDL_RenderPresent(renderer);
        
        
            

        
    }
    
    SDL_FreeSurface(continue_surf);
    SDL_FreeSurface(empty_surf);
    SDL_DestroyTexture(continue_text);
    SDL_DestroyTexture(empty_text);
    
    
}

void About::kill() {
    
    TTF_CloseFont( font );
    TTF_CloseFont(font2 );
    TTF_CloseFont(font2_small);
    
    SDL_DestroyTexture(title_t);
    SDL_FreeSurface(title_s);
    
    SDL_DestroyTexture(title2_t);
    SDL_FreeSurface(title2_s);
    
    SDL_DestroyTexture(one_text);
    SDL_FreeSurface(one_surf);
    
    SDL_DestroyTexture(two_text);
   SDL_FreeSurface(two_surf);
   
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    interim = NULL;
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
}
