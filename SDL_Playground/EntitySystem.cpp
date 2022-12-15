#include "EntitySystem.h"
#include "TransformSystem.h"
#include "CollisionSystem.h"
#include "MovementSystem.h"
#include "SpriteSystem.h"


EntitySystem::EntitySystem(DrawSystem* drawSystem)
{
    transformSystem = new TransformSystem;
    collisionSystem = new CollisionSystem(this);
    movementSystem = new MovementSystem(this);
    spriteSystem = new SpriteSystem(this, drawSystem);
    this->drawSystem = drawSystem;
}

int EntitySystem::CreateEntity()
{
    entities.push_back(Entity());

    return static_cast<int>(entities.size()) -1;
}

void EntitySystem::SetVelocity(int entityID, Float2 velocity)
{
    movementSystem->SetVelocity(entities[entityID].MovementID, velocity);
}

void EntitySystem::AddCollidingEntity(int entityID)
{
    collidingIDs.insert(entityID);
}

std::set<int>* EntitySystem::GetCollidingIDs()
{
    return &collidingIDs;
}

void EntitySystem::Move(int entityID, Float2 offset)
{
    transformSystem->AddOffset(entities[entityID].TransformID, offset);
}

void EntitySystem::MoveTo(int entityID, Float2 position)
{
    transformSystem->SetPosition(entities[entityID].TransformID, position);
}

int EntitySystem::Sweep(int entityID, Float2 velocity)
{
    int collidingEntityID = collisionSystem->Sweep(entities[entityID].CollisionID, velocity);
    return collidingEntityID;
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
    
    Transform* transform = transformSystem->GetTransform(entities[entityID].TransformID);
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
    transformSystem->Update();
    spriteSystem->Update();
    collisionSystem->Update();
    movementSystem->Update();
}

void EntitySystem::Destructor()
{
    transformSystem->Destructor();
    collisionSystem->Destructor();
    movementSystem->Destructor();
    spriteSystem->Destructor();
    entities.clear();
}
