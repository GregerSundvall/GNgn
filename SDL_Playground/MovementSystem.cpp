#include "MovementSystem.h"

#include "Engine.h"


void MovementSystem::Update(TransformSystem& transformSystem)
{
    for (int i = 0; i < movements.size(); ++i)
    {
        Entity* entity = entitySystem->GetEntity(movements[i].EntityID);
        transformSystem.AddOffset(entity->TransformID, movements[i].Velocity);
        
    }
    
}

int MovementSystem::Register(int entityID, Float2 size)
{
    movements.push_back(Movement(entityID, size));
    return movements.size() -1;
}

void MovementSystem::Unregister(int spriteID)
{
    movements[spriteID] = movements[movements.size() -1];
    movements.pop_back();
}

Float2 MovementSystem::Get(int movementID)
{
    return movements[movementID].Velocity;
}

void MovementSystem::Set(int movementID, Float2 newVelocity)
{
    movements[movementID].Velocity = newVelocity;
}

