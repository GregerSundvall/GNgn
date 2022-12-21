#pragma once
#include <vector>
#include "Components.h"
class TransformSystem;
struct Movement;
class EntitySystem;



class MovementSystem
{
    std::vector<Movement> movements;
    EntitySystem* entitySystem;
    
public:
    MovementSystem(EntitySystem* entitySystem) { this->entitySystem = entitySystem; }

    void Update();
    int Register(int entityID, Float2 size);
    void Unregister(int movementID);
    void AssignNewEntityID(int movementID, int newEntityID);
    Float2 GetVelocity(int movementID);
    void SetVelocity(int movementID, Float2 newVelocity);
    int Size() { return static_cast<int>(movements.size()); }
    void Destructor() {movements.clear();}
};
