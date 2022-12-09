#pragma once

struct Float2
{
    float X;
    float Y;
};


struct Transform
{
    int ID = -1;
    Float2 Position;
    Float2 Size;
    Float2 Velocity;

    Transform(Float2 position = Float2(0, 0),
        Float2 size = Float2(0, 0),
        Float2 velocity = Float2(0, 0))
    {
        Position = position;
        Size = size;
        Velocity = velocity;
    }
};
