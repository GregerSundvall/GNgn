#include "MovementSystem.h"

#include "Engine.h"


void MovementSystem::Update()
{
    for (int i = 0; i < movements.size(); ++i)
    {
        entitySystem->Move(movements[i].EntityID, movements[i].Velocity);
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

Float2 MovementSystem::GetVelocity(int movementID)
{
    return movements[movementID].Velocity;
}

void MovementSystem::SetVelocity(int movementID, Float2 newVelocity)
{
    movements[movementID].Velocity = newVelocity;
}

