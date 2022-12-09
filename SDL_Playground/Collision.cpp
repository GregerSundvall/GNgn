#include "Collision.h"

void CollisionSystem::Update()
{
}

bool CollisionSystem::CheckAgainstAll(int colliderID)
{
    bool collision = false;
    for (int i = 0; i < MemberCount; ++i)
    {
        if (!colliders[i].InUse || i == colliderID) { continue; }
        
        if (colliders[colliderID].Right < colliders[i].Left ||
            colliders[colliderID].Left > colliders[i].Right ||
            colliders[colliderID].Lower < colliders[i].Upper ||
            colliders[colliderID].Upper > colliders[i].Lower)
        {
            continue;
        }
        collision = true;
        break;
    }
    return collision;
}

void CollisionSystem::CreateCollider(float centerX, float centerY, int width, int height)
{
    Collider collider = Collider(centerX, centerY, width, height);
    int index;
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        index = recycledIndexes.back();
        colliders[index] = collider;
        recycledIndexes.pop_back();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        index = nextFreshIndex;
        colliders.push_back(collider);
        nextFreshIndex++;
    }
    colliders[index].ID = index; // Let collider know it's own index
    MemberCount++;
}

void CollisionSystem::FreeCollider(int index)
{
    colliders.at(index) = Collider();
    recycledIndexes.push_back(index);
    MemberCount--;
}

void CollisionSystem::Destroy()
{
    colliders.clear();
}
