#include "MovementSystem.h"



void MovementSystem::Update()
{
    for (int i = 0; i < movements.size(); ++i)
    {
        int eID = movements[i].EntityID;
        auto entity = entitySystem->GetEntity(eID);
        
        if (entity->CollisionID == -1) // Entity itself does not have a collider
        {
            entitySystem->Move(eID, movements[i].Velocity);
            continue;
        }

        // Check collision against all other colliders
        int sweepResponse = entitySystem->Sweep(eID, movements[i].Velocity); 
        if (sweepResponse == -1) // No collision
        {
            entitySystem->Move(eID, movements[i].Velocity);
            continue;
        }
        //Collision, kill both.
        entitySystem->DestroyEntity(eID);
        entitySystem->DestroyEntity(sweepResponse);
        
    }
}

int MovementSystem::Register(int entityID, Float2 size)
{
    movements.push_back(Movement(entityID, size));
    return static_cast<int>(movements.size()) -1;
}

void MovementSystem::Unregister(int spriteID)
{
    movements[spriteID] = movements[movements.size() -1];
    movements.pop_back();
}

Float2 MovementSystem::GetVelocity(int movementID)
{
    return movements[movementID].Velocity;
}

void MovementSystem::SetVelocity(int movementID, Float2 newVelocity)
{
    movements[movementID].Velocity = newVelocity;
}

