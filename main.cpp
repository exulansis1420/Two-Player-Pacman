#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "gameplay.hpp"
#include "help.hpp"



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
            Gameplay G;
            G.init();
            G.loop();
            G.kill();
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
