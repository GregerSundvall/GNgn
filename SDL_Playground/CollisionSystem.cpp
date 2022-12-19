#include "CollisionSystem.h"
#include "EntitySystem.h"

#include <iostream>

void CollisionSystem::Update()
{
    for (int i = 0; i < colliders.size(); ++i)
    {
        ScanOverlaps(colliders[i].entityID);
    }
}

void CollisionSystem::ScanOverlaps(int colliderID) // Scan for overlap, 1 vs all other colliders
{
    auto position = colliders[colliderID].Position;
    auto size = colliders[colliderID].Size;
    
    for (int i = 0; i < colliders.size(); ++i)
    {
        if (i == colliderID) { continue; } // Dont check against self.

        auto otherPos = colliders[i].Position;
        auto otherSize = colliders[i].Size;
        if (position.x          > otherPos.x + otherSize.x  ||
            position.x + size.x < otherPos.x                ||
            position.y          > otherPos.y + otherSize.y  ||
            position.y + size.y < otherPos.y )
        {
            continue;
        }

        entitySystem->AddCollidingEntity(colliderID);
        entitySystem->AddCollidingEntity(colliders[colliderID].entityID);
        
        // std::cout << colliders[colliderID].Position.y << std::endl;
        // std::cout << entitySystem->GetPosition(colliders[colliderID].entityID)->y << std::endl;
        // std::cout << colliders[i].Position.y << std::endl;
        // std::cout << entitySystem->GetPosition(colliders[i].entityID)->y << std::endl;
        // std::cout << " " << std::endl;
        
        // return colliders[i].entityID; // Collision. Return other part's entity ID
    }
    
    // return -1; // No collision
}

int CollisionSystem::Register(int EntityID, Float2 position, Float2 size)
{
    colliders.push_back(Collider(EntityID, position, size));
    
    return static_cast<int>(colliders.size()) -1;
}

void CollisionSystem::Unregister(int colliderID)
{
    colliders[colliderID] = colliders[colliders.size() -1];
    colliders.pop_back();
}

void CollisionSystem::Destructor()
{
    colliders.clear();
}
