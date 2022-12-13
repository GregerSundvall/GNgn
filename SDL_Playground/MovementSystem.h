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
    void Update(TransformSystem& transformSystem);
    int Register(int entityID, Float2 size);
    void Unregister(int spriteID);
    Float2 Get(int movementID);
    void Set(int movementID, Float2 newVelocity);
    void Destructor() {movements.clear();}
};
