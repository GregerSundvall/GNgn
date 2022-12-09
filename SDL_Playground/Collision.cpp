#include "Collision.h"


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

int CollisionSystem::Register(Float2 position, Float2 size)
{
    int index;
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        index = recycledIndexes.back();
        recycledIndexes.pop_back();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        index = nextFreshIndex;
        nextFreshIndex++;
    }
    colliders[index] = Collider(position, size);
    colliders[index].ID = index; // Let collider know it's own index. Needed?
    MemberCount++;

    return index;
}

void CollisionSystem::Unregister(int index)
{
    colliders.at(index) = Collider();
    recycledIndexes.push_back(index);
    MemberCount--;
}

void CollisionSystem::Destroy()
{
    colliders.clear();
}
