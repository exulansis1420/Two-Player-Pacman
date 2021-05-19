#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "gameplay.hpp"
#include "help.hpp"
#include "character.hpp"
#include "gameover.hpp"

int menuLogic(std::string s) {
    if(s=="menu") {
        Menu M;
           M.init();
        while ( M.loop() ) {
            SDL_Delay(10);
        }
        M.kill();
        
        return menuLogic(M.newwindow);
    }
    
    else if(s=="start") {
        Character C;
        C.init();
        C.loop();
        C.kill();
        
        if(C.newwindow=="game") {
            
            Gameplay G;
            G.init( C.charInt);
            G.loop();
            G.kill();
            
            if(G.newwindow!="quit")
            {
                GameOver GO;
                GO.init(G.winner);
                GO.loop();
                GO.kill();
                return menuLogic(GO.newwindow);
            }
            
        }
        
    }
    
    else if (s=="help") {
        Help H;
        H.init();
        H.loop();
        H.kill();
        return menuLogic(H.newwindow);
        
    }
    
    else if (s=="about") {
        return 0;
    }
    
    else if (s=="quit") {
        return 0;
    }
    return 0;
}

int main(int argc, char** args)
{
   // int maze[43][73];
      
    menuLogic("menu");
     
    
    return 0;
}
