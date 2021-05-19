#include "help.hpp"

using namespace std;

Help::Help() {
    
    
}

void Help::init() {
    SDL_Init( SDL_INIT_EVERYTHING );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    IMG_Init(IMG_INIT_PNG) ;
    TTF_Init();

    window = SDL_CreateWindow( "PacMan 1.0 - Help", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );


    font = TTF_OpenFont("resources/Fonts/Cheapmot.TTF", 72);
    font2 = TTF_OpenFont("resources/Fonts/emulogic.ttf",40);
    font2_small = TTF_OpenFont("resources/Fonts/emulogic.ttf",20);

    yellow = {255,231,55  };
    white = {255,255,255};
    red = {255,0,0};
    
   
    title_s = TTF_RenderText_Solid(font, "help", yellow);
    title_t = SDL_CreateTextureFromSurface(renderer, title_s);

    /*start_surf = TTF_RenderText_Solid(font2, "start", red);
    start_text = SDL_CreateTextureFromSurface(renderer, start_surf);

    help_surf = TTF_RenderText_Solid(font2, "help", red);
    help_text = SDL_CreateTextureFromSurface(renderer, help_surf);

    about_surf = TTF_RenderText_Solid(font2, "about", red);
    about_text = SDL_CreateTextureFromSurface(renderer, about_surf);

    continue_surf = TTF_RenderText_Solid(font2_small, "press enter to continue", {0,0,255});
    continue_text = SDL_CreateTextureFromSurface(renderer, continue_surf);

    empty_surf = TTF_RenderText_Solid(font2_small, " ", {0,0,255});
    empty_text = SDL_CreateTextureFromSurface(renderer, empty_surf);*/
    
    
    interim = Mix_LoadWAV( "resources/Sounds/pacman_intermission.wav" );
    
}

    
void Help::loop() {
    SDL_Rect dest;
    bool quit=false;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
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

        SDL_RenderPresent(renderer);
        
    }
    
    
}

void Help::kill() {
    
    TTF_CloseFont( font );
    TTF_CloseFont(font2 );
    TTF_CloseFont(font2_small);
    
    SDL_DestroyTexture(title_t);
    SDL_FreeSurface(title_s);
   
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
