#include "EntitySystem.h"

#include <iostream>

#include "CollisionSystem.h"
#include "../Engine.h"
#include "../../SpaceShooter/Game.h" // Change notifyIDchange so this wont be needed
#include "MovementSystem.h"
#include "SpriteSystem.h"


EntitySystem::EntitySystem(Engine* engine)
{
    this->engine = engine;
    transformSystem = new TransformSystem(this);
    collisionSystem = new CollisionSystem(this);
    movementSystem = new MovementSystem(this);
    spriteSystem = new SpriteSystem(this);
}

int EntitySystem::CreateEntity()
{
    int id = static_cast<int>(entities.size());
    entities.emplace_back(Entity(id, this));
    return id;
}

void EntitySystem::SetVelocity(int entityID, Float2 velocity)
{
    movementSystem->SetVelocity(entities[entityID].movementID, velocity);
}

void EntitySystem::AddOffset(int entityID, Float2 velocity)
{
    if (entities[entityID].transformID != -1)
    {
        transformSystem->AddOffset(entities[entityID].transformID, velocity);
    }
    if (entities[entityID].collisionID != -1)
    {
        collisionSystem->AddOffset(entities[entityID].collisionID, velocity);
    }
}

void EntitySystem::Move(int entityID, Float2 offset)
{
    for (int i = 0; i < movementSystem->Size(); ++i)
    {
        // transformSystem
    }
    if (entities[entityID].transformID != -1)
    {
        transformSystem->AddOffset(entities[entityID].transformID, offset);
    }
    if (entities[entityID].collisionID != -1)
    {
        collisionSystem->AddOffset(entities[entityID].collisionID, offset);
    }
}

void EntitySystem::MoveTo(int entityID, Float2 position)
{
    transformSystem->SetPosition(entities[entityID].transformID, position);
}

void EntitySystem::DestroyEntity(int entityID)
{
    RemoveTransform(entityID);
    RemoveCollider(entityID);
    RemoveMovement(entityID);
    RemoveSprite(entityID);

    if (entityID < entities.size() -1) // Move last entity back to newly freed index. Notify Game.
    {
        game->NotifyIdChanged(static_cast<int>(entities.size()) -1, entityID);
        entities[entityID].transformID = entities[entities.size() -1].transformID;
        entities[entityID].movementID = entities[entities.size() -1].movementID;
        entities[entityID].collisionID = entities[entities.size() -1].collisionID;
        entities[entityID].spriteID = entities[entities.size() -1].spriteID;
        transformSystem->AssignNewEntityID(entities[entityID].transformID, entityID);
        movementSystem->AssignNewEntityID(entities[entityID].movementID, entityID);
        collisionSystem->AssignNewEntityID(entities[entityID].collisionID, entityID);
        spriteSystem->AssignNewEntityID(entities[entityID].spriteID, entityID);
    }
    
    entities.pop_back();
    game->NotifyEntityDestroyed(entityID);
}

void EntitySystem::NotifyOverlap(std::vector<int> collidingEntities)
{
    // Just destroy them, for now.
    for (int i = static_cast<int>(collidingEntities.size()) - 1; i >= 0; --i)
    {
        DestroyEntity(collidingEntities[i]);
        collidingEntities.pop_back();
    }

}

void EntitySystem::RemoveTransform(int entityID)
{
    if (entities[entityID].transformID != -1)
    {
        transformSystem->Unregister(entities[entityID].transformID);
        entities[entityID].transformID = -1;
    }
}

void EntitySystem::RemoveCollider(int entityID)
{
    if (entities[entityID].collisionID != -1)
    {
        collisionSystem->Unregister(entities[entityID].collisionID);
        entities[entityID].collisionID = -1;
    }
}

void EntitySystem::RemoveMovement(int entityID)
{
    if (entities[entityID].movementID != -1)
    {
        movementSystem->Unregister(entities[entityID].movementID);
        entities[entityID].movementID = -1;
    }
}

void EntitySystem::RemoveSprite(int entityID)
{
    if (entities[entityID].spriteID != -1)
    {
        spriteSystem->Unregister(entities[entityID].spriteID);
        entities[entityID].spriteID = -1;
    }
}

void EntitySystem::AddTransform(int entityID, Float2 position, Float2 size)
{
    if (entities[entityID].transformID != -1) { RemoveTransform(entityID); } // Remove old, if already present
    
    entities[entityID].transformID = transformSystem->Register(entityID, position, size);
}

void EntitySystem::AddCollider(int entityID) // Creates collider with same position/size as transform.
{
    if (entities[entityID].collisionID != -1) { RemoveCollider(entityID); } // Remove old, if already present
    
    Transform* transform = transformSystem->GetTransform(entities[entityID].transformID);
    entities[entityID].collisionID = collisionSystem->Register(entityID, transform->position, transform->size);
}

void EntitySystem::AddMovement(int entityID, Float2 velocity)
{
    if (entities[entityID].movementID != -1) { RemoveMovement(entityID); } // Remove old, if already present
    
    entities[entityID].movementID = movementSystem->Register(entityID, velocity);
}

void EntitySystem::AddSprite(int entityID, Color color)
{
    if (entities[entityID].spriteID == -1) // Add sprite component if needed
    {
        entities[entityID].spriteID = spriteSystem->Register(entityID, color);
    }
    
    spriteSystem->SetColor(entities[entityID].spriteID, color);
}

void EntitySystem::AddSprite(int entityID, std::string filePath)
{
    if (entities[entityID].spriteID == -1) // Add sprite component if needed
    {
        entities[entityID].spriteID = spriteSystem->Register(entityID, {255, 255, 255, 255});
    }

    spriteSystem->SetTexture(entities[entityID].spriteID, filePath);
}

void EntitySystem::AddSprite(int entityID, std::string text, std::string font)
{
    if (entities[entityID].spriteID == -1) // Add sprite component if needed
        {
        entities[entityID].spriteID = spriteSystem->Register(entityID, {255, 255, 255, 255});
        }

    spriteSystem->SetTexture(entities[entityID].spriteID, text, font);
}

void EntitySystem::Update()
{
    transformSystem->Update();
    movementSystem->Update();
    spriteSystem->Update();
    collisionSystem->Update();
}


