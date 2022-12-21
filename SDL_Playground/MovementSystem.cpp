#include "MovementSystem.h"
#include "EntitySystem.h"


void MovementSystem::Update()
{
    for (int i = 0; i < movements.size(); ++i)
    {
        entitySystem->AddOffset(movements[i].entityID, movements[i].velocity);
    }
}

int MovementSystem::Register(int entityID, Float2 size)
{
    movements.push_back(Movement(entityID, size));
    return static_cast<int>(movements.size()) -1;
}

void MovementSystem::Unregister(int movementID)
{
    if (movementID < movements.size() -1)
    {
        entitySystem->UpdateMovementID(movements[movements.size() -1].entityID, movementID);
        movements[movementID].velocity = movements[movements.size() -1].velocity;
        movements[movementID].entityID = movements[movements.size() -1].entityID;
    }
    
    movements.pop_back();
}

void MovementSystem::AssignNewEntityID(int movementID, int newEntityID) //Used when destroying an entity
{
    movements[movementID].entityID = newEntityID;
}

Float2 MovementSystem::GetVelocity(int movementID)
{
    return movements[movementID].velocity;
}

void MovementSystem::SetVelocity(int movementID, Float2 newVelocity)
{
    movements[movementID].velocity = newVelocity;
}

