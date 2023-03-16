#pragma once
#include <string>
#include <SDL_rect.h>

class EntitySystem;


struct Color
{
    int r, g, b, a;

    Color(int r = 0, int g = 0, int b = 0, int a = 255) 
    {
        this->r = r; this->g = g; this->b = b; this->a = a;
    };
    ~Color() = default;  
};

struct Sprite
{
    int entityID;
    int textureID;
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

class Float2
{
public:
    float x;
    float y;
    Float2(float symmetric) { x = symmetric; y = symmetric; }
    Float2(float x, float y) { this->x = x; this->y = y; }
    Float2& operator += (const Float2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    friend Float2 operator+ (Float2 lhs, Float2 const & rhs)
    {
        lhs += rhs;
        return lhs;
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
    void AddSprite(int textureID);
    void AddSprite(std::string text, std::string fontPath);
};


