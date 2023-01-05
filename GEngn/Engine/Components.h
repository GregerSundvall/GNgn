#pragma once
#include <string>
#include <SDL_rect.h>


struct Color
{
    int r, g, b;
    int a = 255;
};

struct Sprite
{
    int entityID;
    Color color;
    std::string imagePath;
    std::string text;
    std::string fontPath;
};

struct DrawObject
{
    Sprite sprite;
    SDL_Rect rect;
};

struct Float2
{
    float x;
    float y;
    Float2& operator += (const Float2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

struct Transform
{
    int entityID;
    Float2 position;
    Float2 size;
};

struct Collider
{
    int entityID;
    Float2 position;
    Float2 size;

};

struct Movement
{
    int entityID;
    Float2 velocity;
};

struct Entity
{
    // int ID;
    int transformID = -1;
    int movementID = -1;
    int collisionID = -1;
    int spriteID = -1;
};