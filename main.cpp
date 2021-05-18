#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "gameplay.hpp"
#include "help.hpp"
#include "character.hpp"



int main(int argc, char** args)
{
   // int maze[43][73];
      
    
    Menu M;
    if ( !M.init() ) {
        system("pause");
        return 1;
    }
    
    
    while ( M.loop() ) {
        SDL_Delay(10);
    }

    M.kill();
    
    
        if(M.newwindow=="start") {
            Character C;
            C.init();
            C.loop();
            C.kill();
            
            if(C.newwindow=="game") {
                Gameplay G;
                G.init( C.charInt);
                G.loop();
                G.kill();
                
            }
        }
        
        else if(M.newwindow=="help") {
            Help H;
            H.init();
            H.loop();
            H.kill();
        }
        
        else if(M.newwindow=="about") {

        }
     
    
    return 0;
}
