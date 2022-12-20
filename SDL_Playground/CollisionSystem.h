#pragma once
#include <set>
#include <vector>
#include "Components.h"

class EntitySystem;


class CollisionSystem
{
    std::vector<Collider> colliders;
    std::set<int> collidingIDs;
    EntitySystem* entitySystem;
    
public:
    CollisionSystem(EntitySystem* entitySystem) { this->entitySystem = entitySystem; }

    void Update();
    void ScanOverlaps(int colliderID);
    void HandleOverlaps();
    void AddOffset(int colliderID, Float2 offset) {colliders[colliderID].position += offset;}
    int Register(int EntityID, Float2 position, Float2 size);
    void Unregister(int colliderID);
    void Destructor();
    
};
