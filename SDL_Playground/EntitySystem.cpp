#include "EntitySystem.h"


int EntitySystem::CreateEntity()
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
    entities[index].ID = index; // Let entity know it's own index. Needed?
    memberCount++;
    
    return index;
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
