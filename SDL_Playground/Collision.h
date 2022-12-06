#pragma once
#include <array>
#include <vector>

struct Collider
{
    float X;
    float Y;
    int Width;
    int Height;
    bool Enabled = true;
    bool InUse = false;

    Collider()
    {
        X = 0;
        Y = 0;
        Width = 0;
        Height = 0;
    };
    
    Collider(float x, float y, int width, int height)
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }
};

class Collision
{
    std::vector<Collider> Colliders = {Collider()};
    int Capacity = 8;
    int MemberCount = 0;
    
public:

    int CreateCollider(float x, float y, int width, int height)
    {
        int index = -1;
        for (int i = 0; i < Colliders.size(); ++i)
        {
            if (Colliders.at(i).InUse == false)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            Capacity *= 2;
            
            
        }
        Colliders[index].X = x;
        Colliders[index].Y = y;
        Colliders[index].Width = width;
        Colliders[index].Height = height;
        MemberCount++;
        return index;
    }

    void FreeCollider(int index);
    
};
