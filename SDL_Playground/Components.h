#pragma once
#include <SDL_rect.h>


struct Color
{
    int R, G, B;
    int A = 255;
};

struct Sprite
{
    int entityID;
    Color Color;
};

struct DrawObject
{
    Sprite sprite;
    SDL_Rect rect;
};

struct Float2
{
public:
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
    int EntityID;
    Float2 Position;
    Float2 Size;
};

struct Collider
{
    int entityID;
    Float2 Position;
    Float2 Size;

};

struct Movement
{
    int EntityID;
    Float2 Velocity;
};

struct Entity
{
    // int ID;
    int TransformID = -1;
    int MovementID = -1;
    int CollisionID = -1;
    int SpriteID = -1;
};