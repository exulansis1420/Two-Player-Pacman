
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

bool init();
void kill();
bool loop();

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *texture, *text;
TTF_Font* font, *font2;
string ee;

int main(int argc, char** args) {

    if ( !init() ) {
        system("pause");
        return 1;
    }

    while ( loop() ) {
        SDL_Delay(10);
    }

    kill();
    return 0;
}
SDL_Event e;
int ax=0,ay=0;

bool loop() {

    SDL_Rect dest;

    SDL_SetRenderDrawColor( renderer, 0,0,0,0);
    SDL_RenderClear( renderer );
    
    SDL_Rect arrow_out;
    arrow_out.w=50;
    arrow_out.h=50;
    
    int arrow_x[3] = {135,145,135};
    int arrow_y[3] = {200,300,400};
    
    
    
    SDL_Texture* arrowSheet = NULL;
    SDL_Surface* temp = IMG_Load("/Users/tanishq/Downloads/arrow.png");
    arrowSheet = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    
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
            
        }
        if (keys[SDL_SCANCODE_DOWN]){
            ax= (ax+1)%3 ;
            ay= (ay+1)%3 ;
           
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

    SDL_Color yellow = {255,231,55  };
    SDL_Color white = {255,255,255};
    SDL_Color red = {255,0,0};
    SDL_Color clr1=white,clr2=white,clr3=white;
    
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

     {
        SDL_Surface* text_surf = TTF_RenderText_Solid(font, "pacman", yellow);
        text = SDL_CreateTextureFromSurface(renderer, text_surf);

        dest.x = 300 - (text_surf->w / 2.0f);
        dest.y = 70;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, text, NULL, &dest);
         
        
        text_surf = TTF_RenderText_Solid(font2, "start", clr1);
         text = SDL_CreateTextureFromSurface(renderer, text_surf);
         dest.x = 300 - (text_surf->w / 2.0f);
         dest.y = 200;
         dest.w = text_surf->w;
         dest.h = text_surf->h;
         
         SDL_RenderCopy(renderer, text, NULL, &dest);
         
        text_surf = TTF_RenderText_Solid(font2, "help", clr2);
        text = SDL_CreateTextureFromSurface(renderer, text_surf);
        dest.x = 300 - (text_surf->w / 2.0f);
        dest.y = 300;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
         
        SDL_RenderCopy(renderer, text, NULL, &dest);
         
        text_surf = TTF_RenderText_Solid(font2, "about", clr3);
        text = SDL_CreateTextureFromSurface(renderer, text_surf);
        dest.x = 300 - (text_surf->w / 2.0f);
        dest.y = 400;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        
        SDL_RenderCopy(renderer, text, NULL, &dest);
         
        SDL_RenderCopy(renderer, arrowSheet, &arrow_in, &arrow_out);

        SDL_DestroyTexture(text);
        SDL_FreeSurface(text_surf);
    }
    SDL_RenderPresent( renderer );

    return true;
}

bool init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
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

    // Load font
    font = TTF_OpenFont("/Users/tanishq/Downloads/pac-font 2.ttf", 72);
    font2 = TTF_OpenFont("/Users/tanishq/Downloads/emulogic.ttf",40);
    if ( !font ) {
        cout << "Error loading font: " << TTF_GetError() << endl;
        return false;
    }

    // Start sending SDL_Texte events
    SDL_StartTextInput();

    return true;
}

void kill() {
    SDL_StopTextInput();

    TTF_CloseFont( font );
    SDL_DestroyTexture( texture );
    texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
