#include "mazeimage.h"
//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

//Screen dimension constants
const int SCREEN_WIDTH = 665;
const int SCREEN_HEIGHT = 735;

void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Texture* target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    IMG_SavePNG(surface, file_name);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, target);
}

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();
		//Deallocates memory
		~LTexture();
		//Loads image at specified path
		bool loadFromFile( std::string path );
		//Deallocates texture
		void free();
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );
		//Gets image dimensions
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture();
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[17];
LTexture gSpriteSheetTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}
int boundary(std::vector<int> maze, int i)
{
    int cols = 19, rows=21;
    int r = i/cols, c = i%cols;
    //start clockwise from tl
    int b = 0;
    if(r>0&&maze[i-cols]==1)
        b+=2;
    else
        b+=1;
    b*=10;
    if(c<cols-1&&maze[i+1]==1)
        b+=2;
    else
        b+=1;
    b*=10;
    if(r<rows-1&&maze[i+cols]==1)
        b+=2;
    else
        b+=1;
    b*=10;
    if(c>0&&maze[i-1]==1)
        b+=2;
    else
        b+=1;
    return b;
}

int tileType (std::vector<int> maze, int i)
{
    int k = boundary( maze, i);
    if(maze[i]==1){
        switch(k){
            case 1111 : return 1; break;
            case 1112 : return 2; break;
            case 1121 : return 3; break;
            case 1122 : return 4; break;
            case 1211 : return 5; break;
            case 1212 : return 6; break;
            case 1221 : return 7; break;
            case 1222 : return 8; break;
            case 2111 : return 9; break;
            case 2112 : return 10; break;
            case 2121 : return 11; break;
            case 2122 : return 12; break;
            case 2211 : return 13; break;
            case 2212 : return 14; break;
            case 2221 : return 15; break;
            case 2222 : return 16; break;
        }
    }
    else{
        return 0;
    }
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	else{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		else{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* LTexture::getTexture()
{
    return mTexture;
}

bool init()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			printf( "Warning: Linear texture filtering not enabled!" );

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "tiles/spritesheet2.png" ) ){
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else{
        for(int i = 0; i<17;i++){
            gSpriteClips[i].x = i*35;
            gSpriteClips[i].y =    0;
            gSpriteClips[i].w =   35;
            gSpriteClips[i].h =   35;
        }
	}
	return success;
}

void close()
{
	//Free loaded images
	gSpriteSheetTexture.free();
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int saveMap(std::vector<int> maze)
{
    /*for(int i=0; i<28; i++){
        for(int j=0; j<33; j++){
            if(maze[33*i+j]==0)
                std::cout<<"  ";
            else std::cout<<maze[33*i+j]<<" ";
        }
        std::cout<<std::endl;
    }*/
	//Start up SDL and create window
	if( !init() )
		printf( "Failed to initialize!\n" );
	else{
		//Load media
		if( !loadMedia() )
			printf( "Failed to load media!\n" );
		else{
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			while( !quit ){
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT )
						quit = true;
				}
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				int r,c;
				for(int i=0; i<maze.size(); i++)
                {
                    r = i/19; c = i % 19;
                    gSpriteSheetTexture.render( gSpriteClips[0].w*c, gSpriteClips[1].h*r, &gSpriteClips[tileType(maze,i)] );
                }
				//Update screen
				SDL_RenderPresent( gRenderer );
				//save_texture("./map.png", gRenderer, gSpriteSheetTexture.getTexture());
			}
			//std::cout<<"Saving..."<<std::endl;
			//save_texture("map.png", gRenderer, gSpriteSheetTexture.getTexture());
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
