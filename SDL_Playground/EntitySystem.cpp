#include "EntitySystem.h"
// #include "TransformSystem.h"
#include "CollisionSystem.h"
#include "Game.h"
#include "MovementSystem.h"
#include "SpriteSystem.h"


EntitySystem::EntitySystem(DrawSystem* drawSystem, Game* game)
{
    transformSystem = new TransformSystem(this);
    collisionSystem = new CollisionSystem(this);
    movementSystem = new MovementSystem(this);
    spriteSystem = new SpriteSystem(this, drawSystem);
    this->drawSystem = drawSystem;
    this->game = game;
}

int EntitySystem::CreateEntity()
{
    entities.push_back(Entity());

    return static_cast<int>(entities.size()) -1;
}

void EntitySystem::SetVelocity(int entityID, Float2 velocity)
{
    movementSystem->SetVelocity(entities[entityID].movementID, velocity);
}

// void EntitySystem::AddCollidingEntity(int entityID)
// {
//     collidingIDs.insert(entityID);
// }

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

// std::set<int>* EntitySystem::GetCollidingIDs()
// {
//     return &collidingIDs;
// }

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

void EntitySystem::Sweep(int entityID, Float2 velocity)
{
    // collisionSystem->Sweep(entities[entityID].CollisionID, velocity);
    // int collidingEntityID = collisionSystem->Sweep(entities[entityID].CollisionID, velocity);
    // return collidingEntityID;
}

void EntitySystem::DestroyEntity(int entityID)
{
    std::cout << "Destroying" << std::endl;
    std::cout << "E " << entityID << std::endl;
    std::cout << "T " << entities[entityID].transformID << std::endl;
    std::cout << "C " << entities[entityID].collisionID << std::endl;
    std::cout << "M " << entities[entityID].movementID << std::endl;
    std::cout << "S " << entities[entityID].spriteID << std::endl;
    RemoveTransform(entityID);
    RemoveCollider(entityID);
    RemoveMovement(entityID);
    RemoveSprite(entityID);
    game->NotifyEntityDestroyed(entityID);

    game->NotifyIdChanged(entities.size() -1, entityID);
    entities[entityID] = entities[entities.size() -1];
    entities.pop_back();
    std::cout << "After destruction" << std::endl;
    std::cout << "E " << entityID << std::endl;
    std::cout << "T " << entities[entityID].transformID << std::endl;
    std::cout << "C " << entities[entityID].collisionID << std::endl;
    std::cout << "M " << entities[entityID].movementID << std::endl;
    std::cout << "S " << entities[entityID].spriteID << std::endl;
}

// void EntitySystem::DestroyEntities(std::vector<int> entityIDs)
// {
//     for (int i = entityIDs.size() - 1; i >= 0; --i) { DestroyEntity(entityIDs[i]); }
// }

void EntitySystem::NotifyOverlap(std::vector<int> collidingEntities)
{
    for (int entityID : collidingEntities)
    {
        DestroyEntity(entityID);
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
    if (entities[entityID].spriteID != -1) { RemoveSprite(entityID); } // Remove old, if already present
    
    entities[entityID].spriteID = spriteSystem->Register(entityID, color);
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

void EntitySystem::Update()
{
    transformSystem->Update();
    movementSystem->Update();
    spriteSystem->Update();
    collisionSystem->Update();
}

void EntitySystem::Destructor()
{
    transformSystem->Destructor();
    collisionSystem->Destructor();
    movementSystem->Destructor();
    spriteSystem->Destructor();
    entities.clear();
}
