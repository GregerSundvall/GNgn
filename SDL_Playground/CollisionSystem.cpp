#include "CollisionSystem.h"

#include "EntitySystem.h"


void CollisionSystem::Update()
{
}

void CollisionSystem::Sweep(int entityID, int colliderID, Float2 offset)
{
    // bool collision = false;
    float minX = colliders[colliderID].minX() + offset.x;
    float maxX = colliders[colliderID].maxX() + offset.x;
    float minY = colliders[colliderID].minY() + offset.y;
    float maxY = colliders[colliderID].maxY() + offset.y;
    
    for (int i = 0; i < colliders.size(); ++i)
    {
        if (i == colliderID) { continue; }

        if (minX > colliders[i].maxX() ||
            maxX < colliders[i].minX() ||
            minY > colliders[i].maxY() ||
            maxY < colliders[i].minY() )
        {
            continue;
        }

        // collision = true;
        entitySystem->DestroyEntity(entityID);
        entitySystem->DestroyEntity(colliders[i].entityID);
    }
}

int CollisionSystem::Register(int EntityID, Float2 position, Float2 size)
{
    colliders.push_back(Collider(EntityID, position, size));
    
    return colliders.size() -1;
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
