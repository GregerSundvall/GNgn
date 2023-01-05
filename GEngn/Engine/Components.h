#pragma once
#include <string>
#include <SDL_rect.h>

class EntitySystem;


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
    int eID;
    EntitySystem* entitySystem;
    int transformID = -1;
    int movementID = -1;
    int collisionID = -1;
    int spriteID = -1;

    void AddTransform(Float2 position, Float2 size);
    void AddMovement(Float2 velocity);
    void AddCollision();
    void AddSprite(Color color);
    void AddSprite(std::string imagePath);
    void AddSprite(std::string text, std::string fontPath);
};


