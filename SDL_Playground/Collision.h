#pragma once
#include <vector>
#include "Transform.h"

struct Collider
{
    int ID = -1;
    Float2 Position;
    Float2 Size;
    Float2 Velocity;
    
    Collider(Float2 position = Float2(0, 0),
        Float2 size = Float2(0, 0),
        Float2 velocity = Float2(0, 0))
    {
        Position = position;
        Size = size;
        Velocity = velocity;
    }
};

class CollisionSystem
{
    std::vector<Collider> colliders;
    std::vector<int> recycledIndexes;
    int MemberCount = 0;
    int nextFreshIndex = 0;
    
public:

    void Update();
    bool CheckAgainstAll(int colliderID);
    int Register(Float2 position, Float2 size);
    void Unregister(int index);
    void Destroy();
    
};
