#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "gameplay.hpp"

int main(int argc, char** args)
{
    Menu M;
    if ( !M.init() ) {
        system("pause");
        return 1;
    }
    
    
    while ( M.loop() ) {
        SDL_Delay(10);
    }

    M.kill();
    
    while(M.newwindow!="exit") {
        if(M.newwindow=="start") {
            Gameplay G;
            G.init();
            G.loop();
            G.kill();
        }
        
        else if(M.newwindow=="help") {
           
        }
        
        else if(M.newwindow=="about") {

        }
    }
    
   
    
    return 0;
}
