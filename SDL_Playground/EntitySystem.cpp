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
    std::cout <<std::endl << "DestroyEntity start" << std::endl;
    for (int i = 0; i < entities.size(); ++i)
    {
        std::cout << "EntityID " << i << " ";
        std::cout << "x = " << transformSystem->GetPosition(entities[i].transformID)->x << " ";
        std::cout << "y = " << transformSystem->GetPosition(entities[i].transformID)->y << " ";
        std::cout << "TransformID " << entities.at(i).transformID << " ";
        std::cout << "MovementID " << entities.at(i).movementID << " ";
        std::cout << "ColliderID " << entities.at(i).collisionID << " ";
        std::cout << "SpriteID " << entities.at(i).spriteID << " " <<std::endl;
    }
    
    RemoveTransform(entityID);
    RemoveCollider(entityID);
    RemoveMovement(entityID);
    RemoveSprite(entityID);

    if (entityID < entities.size() -1) // Move last entity back to newly freed index. Notify Game.
    {
        game->NotifyIdChanged(entities.size() -1, entityID);
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

    std::cout <<std::endl << "DestroyEntity end" << std::endl;
    for (int i = 0; i < entities.size(); ++i)
    {
        std::cout << "EntityID " << i << " ";
        std::cout << "x = " << transformSystem->GetPosition(entities[i].transformID)->x << " ";
        std::cout << "y = " << transformSystem->GetPosition(entities[i].transformID)->y << " ";
        std::cout << "TransformID " << entities.at(i).transformID << " ";
        std::cout << "MovementID " << entities.at(i).movementID << " ";
        std::cout << "ColliderID " << entities.at(i).collisionID << " ";
        std::cout << "SpriteID " << entities.at(i).spriteID << " " <<std::endl;
    }
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
    if (entities[entityID].spriteID != -1) { RemoveSprite(entityID); } // Remove old, if already present
    
    entities[entityID].spriteID = spriteSystem->Register(entityID, color);
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
