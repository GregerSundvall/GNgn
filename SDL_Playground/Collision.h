#pragma once
#include <vector>

struct Collider
{
    float Left;
    float Right;
    float Upper;
    float Lower;
    int ID = -1;
    bool InUse = false;

public:
    Collider()
    {
        Left = -1;
        Right = -1;
        Upper = -1;
        Lower = -1;
    };
    
    Collider(float centerX, float centerY, int width, int height)
    {
        Left = centerX - width/2;
        Right = centerX + width/2;
        Upper = centerY - height/2;
        Lower = centerY + height/2;
        InUse = true;
    }
};

class Collision
{
    std::vector<Collider> colliders;
    std::vector<int> recycledIndexes;
    int MemberCount = 0;
    int nextFreshIndex = 0;
    
public:

    bool CheckAgainstAll(int colliderID);
    void CreateCollider(float centerX, float centerY, int width, int height);
    void FreeCollider(int index);
    void Destroy();
    
};
