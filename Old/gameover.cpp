#include "gameover.hpp"

using namespace std;

GameOver::GameOver() {

    interim = NULL;
    intro_played = false;
    newwindow = "gameover";
    
}

void GameOver::loop() {

    SDL_Rect dest;

    SDL_Rect pac_in,pac_out,ghost_in,ghost_out;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    bool quit=false;
    
    while(!quit)
    {
        
        while ( SDL_PollEvent( &input ) != 0 ) {
            
            if (input.type == SDL_QUIT) {
                newwindow="quit";
                quit=true;}
            
            if (keys[SDL_SCANCODE_ESCAPE]){
                newwindow="menu";
                quit=true;}
               
            
        }
        
        SDL_SetRenderDrawColor( renderer, 0,0,0,0);
        SDL_RenderClear( renderer );
    
    
        int frame = (SDL_GetTicks() / 300) % 2;
        int frame2 = (SDL_GetTicks() / 100) % 3;
        int frame3 = (SDL_GetTicks() / 100) % 2;
     

        
           SDL_Rect rect;
        
           rect.w = 150;
           rect.h = 150;
        
      
        
        if(winner==0) {
            rect.x = 125;
            rect.y = 175;
            dest.x=300-name1_surf->w/2;
            dest.y=380;
            dest.w = name1_surf->w;
            dest.h = name1_surf->h;
            SDL_RenderCopy(renderer, name1_text, NULL, &dest);
            
        }
        else if(winner==1) {
            
            rect.x = 325;
            rect.y = 175;
            dest.x=300-name2_surf->w/2;
            dest.y=380;
            dest.w = name2_surf->w;
            dest.h = name2_surf->h;
            SDL_RenderCopy(renderer, name2_text, NULL, &dest);
            
        }
        

       // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        
        if(winner==0)
        {
            pac_in.x = frame2*33;
            pac_in.y = 0;
            pac_in.w = 32;
            pac_in.h = 32;
            
            pac_out.x = 300-75;
            pac_out.y = 200;
            pac_out.w = 150;
            pac_out.h = 150;
              
            SDL_RenderCopy(renderer, bigpac, &pac_in, &pac_out);
        }
            
        else {
            ghost_in.x = frame3*33;
            ghost_in.y = 0;
            ghost_in.w = 32;
            ghost_in.h = 32;
            
            ghost_out.x = 300-75;
            ghost_out.y = 200;
            ghost_out.w = 150;
            ghost_out.h = 150;
              
            SDL_RenderCopy(renderer, bigghost, &ghost_in, &ghost_out);
        }
                
        
        
        dest.x = 300 - (title_surf->w / 2.0f);
        dest.y = 40;
        dest.w = title_surf->w;
        dest.h = title_surf->h;
          
        SDL_RenderCopy(renderer, title_text, NULL, &dest);
        
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
            
            if(intro_played==false) {
               Mix_PlayChannel(1, interim, -1);
                intro_played=true;
            }


        SDL_RenderPresent( renderer );
    
    }
}


void GameOver::init(int w) {
    winner =w;
    SDL_Init( SDL_INIT_EVERYTHING );
    
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            cout<<"car";
        }
    
    IMG_Init(IMG_INIT_PNG) ;
    TTF_Init();

    window = SDL_CreateWindow( "PacMan 1.0 - GAME OVER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    
    bigpac = NULL;
    temp = IMG_Load("/Users/tanishq/Downloads/bigpac.png");
    bigpac = SDL_CreateTextureFromSurface(renderer, temp);
    
    bigghost = NULL;
    temp = IMG_Load("/Users/tanishq/Downloads/bigghost.png");
    bigghost = SDL_CreateTextureFromSurface(renderer, temp);


    font = TTF_OpenFont("/Users/tanishq/Downloads/emulogic.ttf", 50);
    font2 = TTF_OpenFont("/Users/tanishq/Downloads/pac-font 2.ttf",40);
    font2_small = TTF_OpenFont("/Users/tanishq/Downloads/emulogic.ttf",15);

    yellow = {255,231,55  };
    white = {255,255,255};
    red = {255,0,0};
    
   
   
    title_surf = TTF_RenderText_Solid(font, "GAME OVER", {0,255,0});
    title_text = SDL_CreateTextureFromSurface(renderer, title_surf);
    
    continue_surf = TTF_RenderText_Solid(font2_small, "press ESC to return to main menu", {0,0,255});
    continue_text = SDL_CreateTextureFromSurface(renderer, continue_surf);
    
    empty_surf = TTF_RenderText_Solid(font2_small, " ", {0,0,255});
    empty_text = SDL_CreateTextureFromSurface(renderer, empty_surf);
    
    name1_surf = TTF_RenderText_Solid(font2, "pacman wins", yellow);
    name1_text = SDL_CreateTextureFromSurface(renderer, name1_surf);
    
    name2_surf = TTF_RenderText_Solid(font2, "blinky wins", {255,0,0});
    name2_text = SDL_CreateTextureFromSurface(renderer, name2_surf);

    
    interim = Mix_LoadWAV( "/Users/tanishq/Downloads/pacman_intermission.wav" );
    
    
}

    

void GameOver::kill() {
    SDL_StopTextInput();

    TTF_CloseFont( font );
    TTF_CloseFont(font2 );
    TTF_CloseFont(font2_small);
   

    SDL_DestroyTexture( continue_text );
    SDL_DestroyTexture( empty_text );
   
    SDL_DestroyTexture( bigpac );
    SDL_DestroyTexture( bigghost );

    SDL_FreeSurface(continue_surf);
    SDL_FreeSurface(empty_surf);
    SDL_FreeSurface(temp);

    
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    

    interim = NULL;
    

    
    Mix_FreeChunk( interim ) ;
  
    
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
