#pragma once


struct Float2
{
    float x;
    float y;
};


struct Color
{
    int R, G, B;
    int A = 255;
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


struct Sprite
{
    int entityID;
    Color Color;
};