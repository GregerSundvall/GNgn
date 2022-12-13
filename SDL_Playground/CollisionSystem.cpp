#include "CollisionSystem.h"


void CollisionSystem::Update()
{
}

bool CollisionSystem::CheckAgainstAll(int colliderID)
{
    bool collision = false;
    // for (int i = 0; i < MemberCount; ++i)
    // {
    //     if (!colliders[i].ID == -1) { continue; }
    //     
    //     if (colliders[colliderID].Right < colliders[i].Left ||
    //         colliders[colliderID].Left > colliders[i].Right ||
    //         colliders[colliderID].Lower < colliders[i].Upper ||
    //         colliders[colliderID].Upper > colliders[i].Lower)
    //     {
    //         continue;
    //     }
    //     collision = true;
    //     break;
    // }
    return collision;
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
