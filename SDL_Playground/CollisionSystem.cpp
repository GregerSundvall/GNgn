#include "CollisionSystem.h"

#include "EntitySystem.h"


void CollisionSystem::Update()
{

}

int CollisionSystem::Sweep(int colliderID, Float2 velocity)
{
    float minX = colliders[colliderID].minX() + velocity.x;
    float maxX = colliders[colliderID].maxX() + velocity.x;
    float minY = colliders[colliderID].minY() + velocity.y;
    float maxY = colliders[colliderID].maxY() + velocity.y;
    
    for (int i = 0; i < colliders.size(); ++i)
    {
        if (i == colliderID) { continue; } // Dont check against self.

        if (minX > colliders[i].maxX() ||
            maxX < colliders[i].minX() ||
            minY > colliders[i].maxY() ||
            maxY < colliders[i].minY() )
        {
            continue;
        }
        return colliders[i].entityID; // Collision. Return other part's entity ID
    }
    
    return -1; // No collision
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
