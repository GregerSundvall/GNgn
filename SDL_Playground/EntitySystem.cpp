#include "EntitySystem.h"
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
    game->NotifyEntityDestroyed(entityID);

    if (entityID < entities.size() -1)
    {
        game->NotifyIdChanged(entities.size() -1, entityID);
        entities[entityID] = entities[entities.size() -1];
    }
    
    entities.pop_back();
}

void EntitySystem::NotifyOverlap(std::vector<int> collidingEntities)
{
    // Just destroy them, for now.
    std::cout << "NotifyOverlap run. Overlaps: " << collidingEntities.size() << std::endl;

    for (int i = collidingEntities.size() - 1; i >= 0; --i)
    {
        std::cout << "In loop, i = : " << i << std::endl;
        std::cout << "In loop, overlaps = " << collidingEntities.size() << std::endl;
        DestroyEntity(collidingEntities[i]);
        collidingEntities.pop_back();
        std::cout << "End of loop iteration, overlaps = " << collidingEntities.size() << std::endl;
    }
    std::cout << "NotifyOverlap out of loop. Overlaps: " << collidingEntities.size() << std::endl;
    
    // while (collidingEntities.size() > 1)
    // {
    //     DestroyEntity(*collidingEntities.rbegin());
    //     std::cout << collidingEntities.size() << std::endl;
    //     std::cout << *collidingEntities.rbegin() << std::endl;
    //     collidingEntities.erase(*collidingEntities.rbegin());
    //     std::cout << collidingEntities.size() << std::endl;
    //     std::cout << std::endl;
    // }
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
