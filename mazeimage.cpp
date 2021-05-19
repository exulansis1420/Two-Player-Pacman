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
#include "dots.h"

//Screen dimension constants
const int SCREEN_WIDTH = 570;
const int SCREEN_HEIGHT = 630;

// Save screenshot
// file: Filename for created screenshot
// renderer: pointer to SDL_Renderer
bool saveScreenshot(const std::string &file, SDL_Renderer *renderer ) {
  // Used temporary variables
  SDL_Rect _viewport;
  SDL_Surface *_surface = NULL;

  // Get viewport size
  SDL_RenderGetViewport( renderer, &_viewport);

  // Create SDL_Surface with depth of 32 bits
  _surface = SDL_CreateRGBSurface( 0, _viewport.w, _viewport.h, 32, 0, 0, 0, 0 );

  // Check if the surface is created properly
  if ( _surface == NULL ) {
    std::cout << "Cannot create SDL_Surface: " << SDL_GetError() << std::endl;
    return false;
   }

  // Get data from SDL_Renderer and save them into surface
  if ( SDL_RenderReadPixels( renderer, NULL, _surface->format->format, _surface->pixels, _surface->pitch ) != 0 ) {
    std::cout << "Cannot read data from SDL_Renderer: " << SDL_GetError() << std::endl;

    // Don't forget to free memory
    SDL_FreeSurface(_surface);
    return false;
  }

  // Save screenshot as PNG file
  if ( IMG_SavePNG( _surface, file.c_str() ) != 0 ) {
    std::cout << "Cannot save PNG file: " << SDL_GetError() << std::endl;

    // Free memory
    SDL_FreeSurface(_surface);
    return false;
  }

  // Free memory
  SDL_FreeSurface(_surface);
  return true;
}

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename)
{
    SDL_Texture *ren_tex;
    SDL_Surface *surf;
    int st;
    int w;
    int h;
    int format;
    void *pixels;

    pixels  = NULL;
    surf    = NULL;
    ren_tex = NULL;
    format  = SDL_PIXELFORMAT_RGBA32;

    /* Get information about texture we want to save */
    st = SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    if (st != 0) {
        SDL_Log("Failed querying texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    ren_tex = SDL_CreateTexture(ren, format, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we
     * can access
     */
    st = SDL_SetRenderTarget(ren, ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);

    st = SDL_RenderCopy(ren, tex, NULL, NULL);
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        goto cleanup;
    }

    st = SDL_RenderReadPixels(ren, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Save result to an image */
    st = SDL_SaveBMP(surf, filename);
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Log("Saved texture as BMP to \"%s\"\n", filename);

cleanup:
    SDL_FreeSurface(surf);
    free(pixels);
    SDL_DestroyTexture(ren_tex);
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
SDL_Rect gSpriteClips[2];
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
    //int k = boundary( maze, i);
    if(maze[i]==1){
        return 1;
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
        gWindow = SDL_CreateWindow( "MAP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    if( !gSpriteSheetTexture.loadFromFile( "/Users/tanishq/Downloads/spritesheet2.png" ) ){
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else{
        for(int i = 0; i<2;i++){
            gSpriteClips[i].x = i*30;
            gSpriteClips[i].y =    0;
            gSpriteClips[i].w =   30;
            gSpriteClips[i].h =   30;
        }
    }
    return success;
}

bool loadMedia2()
{
    //Loading success flag
    bool success = true;
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "tiles/dotspritesheet.png" ) ){
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else{
        for(int i = 0; i<2;i++){
            gSpriteClips[i].x = i*30;
            gSpriteClips[i].y =    0;
            gSpriteClips[i].w =   30;
            gSpriteClips[i].h =   30;
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
              //  SDL_RenderPresent( gRenderer );
                if(saveScreenshot("map.png", gRenderer ))
                    break;
                //save_texture("./map.png", gRenderer, gSpriteSheetTexture.getTexture());
            }
            //std::cout<<"Saving..."<<std::endl;

        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

int display(std::vector<int> dots)
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
        if( !loadMedia2() )
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
                for(int i=0; i<dots.size(); i++)
                {
                    r = i/19; c = i % 19;
                    if(dots[i]!=0)
                        gSpriteSheetTexture.render( gSpriteClips[0].w*c, gSpriteClips[1].h*r, &gSpriteClips[tileType(dots,i)] );
                }
                //Update screen
                SDL_RenderPresent( gRenderer );
                //if(saveScreenshot("dots.png", gRenderer ))
                    //break;
                //save_texture("./map.png", gRenderer, gSpriteSheetTexture.getTexture());
            }
            //std::cout<<"Saving..."<<std::endl;

        }
    }

    //Free resources and close SDL
    close();

    return 0;
}


