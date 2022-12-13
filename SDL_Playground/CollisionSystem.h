#pragma once
#include <vector>
#include "Components.h"



class CollisionSystem
{
    std::vector<Collider> colliders;
    
public:

    void Update();
    bool CheckAgainstAll(int colliderID);
    int Register(int EntityID, Float2 position, Float2 size);
    void Unregister(int index);
    void Destructor();
    
};
