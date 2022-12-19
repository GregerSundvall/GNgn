#include "CollisionSystem.h"
#include "EntitySystem.h"

#include <iostream>

void CollisionSystem::Update()
{
    for (int i = 0; i < colliders.size(); ++i)
    {
        ScanOverlaps(colliders[i].entityID);
    }
    HandleOverlaps();
}

void CollisionSystem::ScanOverlaps(int colliderID) // Scan for overlap, 1 vs all other colliders
{
    auto position = colliders[colliderID].position;
    auto size = colliders[colliderID].size;
    
    for (int i = 0; i < colliders.size(); ++i)
    {
        if (i == colliderID) { continue; } // Dont check against self.

        auto otherPos = colliders[i].position;
        auto otherSize = colliders[i].size;
        if (position.x          > otherPos.x + otherSize.x  ||
            position.x + size.x < otherPos.x                ||
            position.y          > otherPos.y + otherSize.y  ||
            position.y + size.y < otherPos.y )
        {
            continue;
        }
        collidingIDs.insert(colliderID);
        collidingIDs.insert(colliders[i].entityID);
    }
}

void CollisionSystem::HandleOverlaps()
{
    if (collidingIDs.size() > 0)
    {
        std::vector<int> entityIDs;
        for (int entityID : collidingIDs)
        {
            entityIDs.push_back(entityID);
        }

        collidingIDs.clear();
        entitySystem->NotifyOverlap(entityIDs);
    }
}

int CollisionSystem::Register(int EntityID, Float2 position, Float2 size)
{
    colliders.push_back(Collider(EntityID, position, size));
    
    return static_cast<int>(colliders.size()) -1;
}

void CollisionSystem::Unregister(int colliderID)
{
    entitySystem->UpdateColliderID(colliders[colliders.size() -1].entityID, colliderID);
    Collider temp = colliders[colliders.size() -1];
    colliders[colliderID] = temp;
    colliders.pop_back();
}

void CollisionSystem::Destructor()
{
    colliders.clear();
}
