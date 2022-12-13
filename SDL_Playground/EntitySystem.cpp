#include "EntitySystem.h"

#include "TransformSystem.h"


int EntitySystem::CreateEntity()
{
    entities.push_back(Entity(entities.size()));

    return entities.size() -1;
}

void EntitySystem::DestroyEntity(int entityID)
{
    RemoveTransform(entityID);
    RemoveCollider(entityID);
    RemoveMovement(entityID);
    RemoveSprite(entityID);
    
    entities[entityID] = entities[entities.size() -1];
    entities.pop_back();
}

void EntitySystem::AddTransform(int entityID, Float2 position, Float2 size)
{
    if (entities[entityID].TransformID != -1) { RemoveTransform(entityID); } // Remove old, if already present
    
    entities[entityID].TransformID = transformSystem->Register(entityID, position, size);
}

void EntitySystem::AddCollider(int entityID) // Creates collider with same position/size as transform.
{
    if (entities[entityID].CollisionID != -1) { RemoveCollider(entityID); } // Remove old, if already present
    
    Transform* transform = transformSystem->GetPosition(entities[entityID].TransformID);
    entities[entityID].CollisionID = collisionSystem->Register(entityID, transform->Position, transform->Size);
}

void EntitySystem::AddMovement(int entityID, Float2 velocity)
{
    if (entities[entityID].MovementID != -1) { RemoveMovement(entityID); } // Remove old, if already present
    
    entities[entityID].MovementID = movementSystem->Register(entityID, velocity);
}

void EntitySystem::AddSprite(int entityID, Color color)
{
    if (entities[entityID].SpriteID != -1) { RemoveSprite(entityID); } // Remove old, if already present
    
    entities[entityID].SpriteID = spriteSystem->Register(entityID, color);
}

void EntitySystem::RemoveTransform(int entityID)
{
    if (entities[entityID].TransformID != -1)
    {
        transformSystem->Unregister(entities[entityID].TransformID);
        entities[entityID].TransformID = -1;
    }
}

void EntitySystem::RemoveCollider(int entityID)
{
    if (entities[entityID].CollisionID != -1)
    {
        collisionSystem->Unregister(entities[entityID].CollisionID);
        entities[entityID].CollisionID = -1;
    }
}

void EntitySystem::RemoveMovement(int entityID)
{
    if (entities[entityID].MovementID != -1)
    {
        movementSystem->Unregister(entities[entityID].MovementID);
        entities[entityID].MovementID = -1;
    }
}

void EntitySystem::RemoveSprite(int entityID)
{
    if (entities[entityID].SpriteID != -1)
    {
        spriteSystem->Unregister(entities[entityID].SpriteID);
        entities[entityID].SpriteID = -1;
    }
}

void EntitySystem::Update()
{
    movementSystem->Update();
    collisionSystem->Update();
    transformSystem->Update();
}

void EntitySystem::Destructor()
{
    transformSystem->Destructor();
    collisionSystem->Destructor();
    movementSystem->Destructor();
    spriteSystem->Destructor();
    entities.clear();
}
