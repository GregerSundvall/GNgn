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
    Float2 Velocity;

    Transform()
    {
        Position = Float2(-1, -1);
        Velocity = Float2(0, 0);
    }

    Transform(Float2 position, Float2 velocity)
    {
        Position = position;
        Velocity = velocity;
    }
};
