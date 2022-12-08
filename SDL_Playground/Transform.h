#pragma once

struct Vector2
{
    float X;
    float Y;
};


struct Transform
{
    int ID = -1;
    Vector2 Position;
    Vector2 Velocity;

    Transform()
    {
        ID = -1;
        Position = Vector2(-1, -1);
        Velocity = Vector2(0, 0);
    }

    Transform(Vector2 position, Vector2 velocity)
    {
        Position = position;
        Velocity = velocity;
    }
};
