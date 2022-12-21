#include "CollisionSystem.h"

#include <iostream>

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
        std::cout << "Inserted " << colliderID << " and " << i << " into collidingIDs" << std::endl;
        std::cout << colliderID << " (this) position: " << colliders[colliderID].position.y << std::endl;
        std::cout << i << " (other) position: " << colliders[i].position.y << std::endl;
    }
}

void CollisionSystem::HandleOverlaps()
{
    if (collidingIDs.size() == 0) { return; }
    std::cout << "HandleOverlaps start. Count = " << collidingIDs.size() << std::endl;
    std::cout << "ID " << *collidingIDs.begin() << std::endl;
    std::cout << "ID " << *collidingIDs.rbegin() << std::endl;
    
    std::vector<int> entityIDs;
    for (int cID : collidingIDs)
    {
        entityIDs.push_back(colliders[cID].entityID);
    }
    collidingIDs.clear();
    std::cout << "HandleOverlaps sending " << entityIDs.size() << " ID's to NotifyOverlap" << std::endl;
    entitySystem->NotifyOverlap(entityIDs);
    std::cout << "HandleOverlaps end" << std::endl;
    std::cout << "HandleOverlaps end. " << collidingIDs.size() << " ID's in collidingIDs" << std::endl;
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
