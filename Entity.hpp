#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

public:
    Entity();
    Entity(float x,float y,float w, float h);

    float getScreenPosX();
    float getScreenPosY();
    int getTileX();
    int getTileY();
    SDL_Rect getEntRect();
    void setimage(SDL_Texture* &spriteSheet ,SDL_Rect &textureRect, SDL_Renderer* &renderer);
    void move(float x, float y);
    void teleport(int x, int y);
};
