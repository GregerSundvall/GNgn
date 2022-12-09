#include "EntitySystem.h"

#include "Transform.h"


int EntitySystem::CreateEntity(Float2 position, bool addTransform = true, bool addCollider = true, Float2 size = Float2(4, 4))
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
    
    entities[index] = Entity();
    entities[index].ID = index; // Let entity know it's own index. Not needed?
    if (addTransform) { AddTransform(index, position, size); }
    if (addCollider) { AddCollider(index); }

    memberCount++;
    
    return index;
}

void EntitySystem::AddTransform(int entityID, Float2 position, Float2 size)
{
    entities[entityID].TransformID = transformSystem->Register(position, size);
}

void EntitySystem::AddCollider(int entityID)
{
    // Creates collider with same position/size as transform.
    Transform* transform = transformSystem->GetTransform(entities[entityID].TransformID);
    entities[entityID].CollisionID = collisionSystem->Register(transform->Position, transform->Size);
}

void EntitySystem::Update()
{
    transformSystem->Update();
    collisionSystem->Update();
}

void EntitySystem::Destroy()
{
    transformSystem->Destroy();
    collisionSystem->Destroy();
    entities.clear();
    recycledIndexes.clear();
}
