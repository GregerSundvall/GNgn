#include "TransformSystem.h"

#include <iostream>

#include "Engine.h"
#include "Components.h"
#include "EntitySystem.h"

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
    std::cout << "Unregister start. transforms.size = " << transforms.size() << std::endl;
    if (transformID < transforms.size() -1)
    {
        entitySystem->UpdateTransformID(transforms[transforms.size() -1].entityID, transformID);
        transforms[transformID].position = transforms[transforms.size() -1].position;
        transforms[transformID].size = transforms[transforms.size() -1].size;
        transforms[transformID].entityID = transforms[transforms.size() -1].entityID;
    }
    
    transforms.pop_back();
    std::cout << "Unregister end. transforms.size = " << transforms.size() << std::endl;
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

void TransformSystem::Destructor()
{
    transforms.clear();
}
