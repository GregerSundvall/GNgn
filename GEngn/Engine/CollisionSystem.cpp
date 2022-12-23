#include "CollisionSystem.h"
#include "EntitySystem.h"


void CollisionSystem::Update()
{
    for (int i = 0; i < colliders.size(); ++i)
    {
        ScanOverlaps(i);
    }
    HandleOverlaps();
}

void CollisionSystem::ScanOverlaps(int colliderID) // Scan for overlap, "this" vs all other colliders
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
        collidingIDs.insert(i);
    }
}

void CollisionSystem::HandleOverlaps()
{
    if (collidingIDs.size() == 0) { return; }
    
    std::vector<int> entityIDs;
    for (int cID : collidingIDs)
    {
        entityIDs.push_back(colliders[cID].entityID);
    }
    collidingIDs.clear();
    entitySystem->NotifyOverlap(entityIDs);
}

int CollisionSystem::Register(int EntityID, Float2 position, Float2 size)
{
    colliders.push_back(Collider(EntityID, position, size));
    
    return static_cast<int>(colliders.size()) -1;
}

void CollisionSystem::Unregister(int colliderID)
{
    if (colliderID < colliders.size() -1)
    {
        entitySystem->UpdateColliderID(colliders[colliders.size() -1].entityID, colliderID);
        colliders[colliderID].position = colliders[colliders.size() -1].position;
        colliders[colliderID].size = colliders[colliders.size() -1].size;
        colliders[colliderID].entityID = colliders[colliders.size() -1].entityID;
    }
    
    colliders.pop_back();
}

void CollisionSystem::AssignNewEntityID(int colliderID, int newEntityID) //Used when destroying an entity
{
    colliders[colliderID].entityID = newEntityID;
}

void CollisionSystem::Destructor()
{
    colliders.clear();
}
