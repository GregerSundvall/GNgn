#pragma once
#include <vector>
#include "Components.h"
struct Float2;
struct Transform;
class EntitySystem;


class TransformSystem
{
    std::vector<Transform> transforms;
    EntitySystem* entitySystem;
    
public:
    TransformSystem(EntitySystem* entitySystem) { this->entitySystem = entitySystem; }
    void Update();
    int Register(int EntityID, Float2 position, Float2 size);
    void Unregister(int transformID);
    void AssignNewEntityID(int transformID, int newEntityID);
    Float2* GetPosition(int transformID);
    Transform* GetTransform(int transformID);
    void SetPosition(int transformID, Float2 position) {transforms[transformID].position = position;}
    void AddOffset(int transformID, Float2 offset) {transforms[transformID].position += offset;}
    void Destructor();
    
};
