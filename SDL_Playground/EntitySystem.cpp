#include "EntitySystem.h"

#include "Transform.h"


int EntitySystem::CreateEntity(Float2 position, bool addTransform, bool addCollider, Float2 size)
{
    int index;
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        index = recycledIndexes.back();
        recycledIndexes.pop_back();
        entities[index] = Entity();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        index = nextFreshIndex;
        nextFreshIndex++;
        entities.push_back(Entity());
    }
    
    entities[index].ID = index; // Let entity know it's own index. Not needed?
    
    if (addTransform) { AddTransform(index, position, size); }
    if (addCollider) { AddCollider(index); }

    memberCount++;
    
    return index;
}

void EntitySystem::DestroyEntity(int entityID)
{
    RemoveTransform(entityID);
    if (entities[entityID].CollisionID != -1)
    {
        // Unregister from collisionSystem
    }
    if (entities[entityID].MovementID != -1)
    {
        // Unregister from movementSystem
    }
    if (entities[entityID].SpriteID != -1)
    {
        // Unregister from spriteSystem
    }

    entities[entityID] = entities[entities.size() -1];
    entities.pop_back();
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

void EntitySystem::AddMovement(int entityID, Float2 velocity)
{
    entities[entityID].MovementID = movementSystem->Register(entityID, velocity);
}

void EntitySystem::AddSprite(int entityID, Color color)
{
    entities[entityID].SpriteID = spriteSystem->Register(entityID, color);
}

void EntitySystem::RemoveTransform(int entityID)
{
    transformSystem->Unregister(entities[entityID].TransformID);
    entities[entityID].TransformID = -1;
}

void EntitySystem::RemoveCollider(int entityID)
{
    collisionSystem->Unregister(entities[entityID].CollisionID);
    entities[entityID].CollisionID = -1;
}

void EntitySystem::RemoveMovement(int entityID)
{
    movementSystem->Unregister(entities[entityID].MovementID);
    entities[entityID].MovementID = -1;
}

void EntitySystem::RemoveSprite(int entityID)
{
    spriteSystem->Unregister(entities[entityID].SpriteID);
    entities[entityID].SpriteID = -1;
}

void EntitySystem::Update()
{
    transformSystem->Update();
    movementSystem->Update();
    collisionSystem->Update();
}

void EntitySystem::Destructor()
{
    transformSystem->Destructor();
    collisionSystem->Destructor();
    entities.clear();
    recycledIndexes.clear();
}
