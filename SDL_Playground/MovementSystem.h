#pragma once
#include <vector>

#include "Components.h"
#include "EntitySystem.h"
class TransformSystem;
struct Movement;



class MovementSystem
{
    std::vector<Movement> movements;
    EntitySystem* entitySystem;
    
    MovementSystem(EntitySystem* entitySystem)
    {
        this->entitySystem = entitySystem;
    }

public:
    void Update();
    int Register(int entityID, Float2 size);
    void Unregister(int spriteID);
    Float2 GetVelocity(int movementID);
    void SetVelocity(int movementID, Float2 newVelocity);
    void Destructor() {movements.clear();}
};
