#pragma once

struct Collider;
struct Transform;

struct Color
{
    int R;
    int G;
    int B;
    int A = 255;
};


struct Entity
{
    int transformID;
    int colliderID;
    Color Color = {100, 100, 100};


};
