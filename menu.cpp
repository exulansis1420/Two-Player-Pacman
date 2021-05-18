
#include "menu.hpp"
#include "gameplay.hpp"

using namespace std;

Menu::Menu() {
    menuchange = NULL;
    intro = NULL;
    interim = NULL;
    ax=0;
    ay=0;
    intro_played = false;
    newwindow = "menu";
    texture = NULL;
    text=NULL;
    
}



bool Menu::loop() {

    SDL_Rect dest;

    SDL_SetRenderDrawColor( renderer, 0,0,0,0);
    SDL_RenderClear( renderer );

    SDL_Rect arrow_out;
    arrow_out.w=50;
    arrow_out.h=50;
    
    int arrow_x[3] = {135,145,135};
    int arrow_y[3] = {200,300,400};
    
    SDL_Color clr1=white, clr2=white, clr3=white;
 

    SDL_Rect arrow_in;
    arrow_in.x = 0;
    arrow_in.y = 0;
    SDL_QueryTexture(arrowSheet, NULL, NULL, &arrow_in.w, &arrow_in.h);
    arrow_in.h /= 2;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
 
    while ( SDL_PollEvent( &e ) != 0 ) {
        
        if (e.type == SDL_QUIT) return false;
        if (keys[SDL_SCANCODE_UP]){
            ax= (ax-1)%3 ;
            ay= (ay-1)%3 ;
            
            if(ax<0 && ay<0){
                ax+=3;
                ay+=3;
            }
            Mix_PlayChannel( -1, menuchange, 0 );
            
        }
        if (keys[SDL_SCANCODE_DOWN]){
            ax= (ax+1)%3 ;
            ay= (ay+1)%3 ;
            Mix_PlayChannel( -1, menuchange, 0 );
           
        }
        
        if (keys[SDL_SCANCODE_RETURN]){
            newwindow="start";
            return false;
           
        }
        
    }
    
    
    int totalFrames = 2;
    int delayPerFrame = 300;
    int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
    
    arrow_out.x=arrow_x[ax];
    arrow_out.y=arrow_y[ay];
    
    if(frame%2==1) {
        arrow_in.y = 0;
    }
    else {
        arrow_in.x = arrow_in.h;
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    
    if(ax==0) {
        clr1=red;
        clr2=white;
        clr3=white;
    }
    else if(ax==1) {
        clr1=white;
        clr2=red;
        clr3=white;
    }
    else if(ax==2) {
        clr1=white;
        clr2=white;
        clr3=red;
    }

        dest.x = 300 - (pacman_surf->w / 2.0f);
        dest.y = 70;
        dest.w = pacman_surf->w;
        dest.h = pacman_surf->h;
        SDL_RenderCopy(renderer, pacman_text, NULL, &dest);
         
         dest.x = 300 - (start_surf->w / 2.0f);
         dest.y = 200;
         dest.w = start_surf->w;
         dest.h = start_surf->h;
         
         SDL_RenderCopy(renderer, start_text, NULL, &dest);
         
        dest.x = 300 - (help_surf->w / 2.0f);
        dest.y = 300;
        dest.w = help_surf->w;
        dest.h = help_surf->h;
        SDL_RenderCopy(renderer, help_text, NULL, &dest);
         

        dest.x = 300 - (about_surf->w / 2.0f);
        dest.y = 400;
        dest.w = about_surf->w;
        dest.h = about_surf->h;
        
        SDL_RenderCopy(renderer, about_text, NULL, &dest);
         
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


        SDL_RenderCopy(renderer, arrowSheet, &arrow_in, &arrow_out);

        SDL_RenderPresent( renderer );
    
    if(intro_played==false) {
        Mix_PlayChannel( -1, intro, 0 );
        intro_played=true;
    }
    
    return true;
}

bool Menu::init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                   {
                       cout<< "SDL_mixer could not initialize! SDL_mixer Error: \n"<< Mix_GetError() ;
                       return false;
                   }

    if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
        cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
        return false;
    }

    // Initialize SDL_ttf
    if ( TTF_Init() < 0 ) {
        cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow( "PacMan 1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 650, SDL_WINDOW_SHOWN );
    if ( !window ) {
        cout << "Error creating window: " << SDL_GetError()  << endl;
        return false;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if ( !renderer ) {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("/Users/tanishq/Downloads/pac-font 2.ttf", 72);
    font2 = TTF_OpenFont("/Users/tanishq/Downloads/emulogic.ttf",40);
    font2_small = TTF_OpenFont("/Users/tanishq/Downloads/emulogic.ttf",20);

    yellow = {255,231,55  };
    white = {255,255,255};
    red = {255,0,0};
    
    arrowSheet = NULL;
    temp = IMG_Load("/Users/tanishq/Downloads/arrow.png");
    arrowSheet = SDL_CreateTextureFromSurface(renderer, temp);


    pacman_surf = TTF_RenderText_Solid(font, "pacman", yellow);
    pacman_text = SDL_CreateTextureFromSurface(renderer, pacman_surf);

    start_surf = TTF_RenderText_Solid(font2, "start", red);
    start_text = SDL_CreateTextureFromSurface(renderer, start_surf);

    help_surf = TTF_RenderText_Solid(font2, "help", red);
    help_text = SDL_CreateTextureFromSurface(renderer, help_surf);

    about_surf = TTF_RenderText_Solid(font2, "about", red);
    about_text = SDL_CreateTextureFromSurface(renderer, about_surf);

    continue_surf = TTF_RenderText_Solid(font2_small, "press enter to continue", {0,0,255});
    continue_text = SDL_CreateTextureFromSurface(renderer, continue_surf);

    empty_surf = TTF_RenderText_Solid(font2_small, " ", {0,0,255});
    empty_text = SDL_CreateTextureFromSurface(renderer, empty_surf);
    
    
    
    menuchange = Mix_LoadWAV( "/Users/tanishq/Downloads/change-menu.wav" );
    if( menuchange == NULL )
    {
        cout<< "Failed to load change menu sound effect! SDL_mixer Error: %s\n"<< Mix_GetError() <<endl;
        return false;
    }
    
    intro = Mix_LoadWAV( "/Users/tanishq/Downloads/pacman_beginning.wav" );
    if( menuchange == NULL )
    {
        cout<< "Failed to load change menu sound effect! SDL_mixer Error: %s\n"<< Mix_GetError() <<endl;
        return false;
    }
    
    interim = Mix_LoadWAV( "/Users/tanishq/Downloads/pacman_intermission.wav" );
    if( menuchange == NULL )
    {
        cout<< "Failed to load change menu sound effect! SDL_mixer Error: %s\n"<< Mix_GetError() <<endl;
        return false;
    }

    SDL_StartTextInput();

    return true;
}

void Menu::kill() {
    SDL_StopTextInput();

    TTF_CloseFont( font );
    SDL_DestroyTexture( texture );
    texture = NULL;
    
    SDL_DestroyTexture( pacman_text );
    SDL_DestroyTexture( start_text );
    SDL_DestroyTexture( continue_text );
    SDL_DestroyTexture( empty_text );
    SDL_DestroyTexture( help_text );
    SDL_DestroyTexture( about_text );
    SDL_DestroyTexture( arrowSheet );
    
    SDL_FreeSurface(pacman_surf);
    SDL_FreeSurface(about_surf);
    SDL_FreeSurface(help_surf);
    SDL_FreeSurface(start_surf);
    SDL_FreeSurface(continue_surf);
    SDL_FreeSurface(empty_surf);
    SDL_FreeSurface(temp);
    
    

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    
    menuchange = NULL;
    intro = NULL;
    interim = NULL;
    

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
