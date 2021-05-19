#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class Entity
{
protected:
    int tileX;
    int tileY;
    float screenPosX;
    float screenPosY;
    float width;
    float height;
    SDL_Rect entRect;
    bool play_intro,pacdead;
    Mix_Chunk *intro , *interim, *siren, *dead, *munch, *fruit, *largepel, *eatghost;
  

public:
    Entity();
    Entity(float x,float y,float w, float h);
    Uint32 five_start;
    float getScreenPosX();
    float getScreenPosY();
    int getTileX();
    int getTileY();
    SDL_Rect getEntRect();
    void setimage(SDL_Texture* &spriteSheet ,SDL_Rect &textureRect, SDL_Renderer* &renderer, int ch);
    void move(float x, float y);
    void teleport(int x, int y);
};
