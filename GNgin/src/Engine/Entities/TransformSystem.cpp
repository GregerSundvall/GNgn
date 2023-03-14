#include "TransformSystem.h"
#include "../Misc/Components.h"
#include "EntitySystem.h"

TransformSystem::TransformSystem(EntitySystem* entitySystem)
{
    this->entitySystem = entitySystem; 
}

void TransformSystem::Update()
{

}

int TransformSystem::Register(int EntityID, Float2 position, Float2 size)
{
    transforms.push_back(Transform(EntityID, position, size));
    
    return static_cast<int>(transforms.size()) -1;
}

void TransformSystem::Unregister(int transformID)
{
    if (transformID < transforms.size() -1)
    {
        entitySystem->UpdateTransformID(transforms[transforms.size() -1].entityID, transformID);
        transforms[transformID].position = transforms[transforms.size() -1].position;
        transforms[transformID].size = transforms[transforms.size() -1].size;
        transforms[transformID].entityID = transforms[transforms.size() -1].entityID;
    }
    
    transforms.pop_back();
}

void TransformSystem::AssignNewEntityID(int transformID, int newEntityID) //Used when destroying an entity
{
    transforms[transformID].entityID = newEntityID;
}

Float2* TransformSystem::GetPosition(int transformID)
{
    return &transforms[transformID].position;
}

Transform* TransformSystem::GetTransform(int transformID)
{
    return &transforms[transformID];
}

void TransformSystem::SetPosition(int transformID, Float2 position)
{
    transforms[transformID].position = position;
}

void TransformSystem::AddOffset(int transformID, Float2 offset)
{
    transforms[transformID].position += offset;
}
