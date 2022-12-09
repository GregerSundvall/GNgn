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
    int ID;
    int TransformID = -1;
    int ColliderID = -1;
    Color Color = {100, 100, 100};
};
