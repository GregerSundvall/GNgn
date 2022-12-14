#include "TransformSystem.h"
#include "Engine.h"
#include "Components.h"

void TransformSystem::Update()
{

}

int TransformSystem::Register(int EntityID, Float2 position, Float2 size)
{
    transforms.push_back(Transform(EntityID, position, size));
    
    return transforms.size() -1;
}

void TransformSystem::Unregister(int transformID)
{
    transforms[transformID] = transforms[transforms.size() -1];
    transforms.pop_back();
}

Transform* TransformSystem::GetPosition(int id)
{
    return &transforms[id];
}

void TransformSystem::Destructor()
{
    transforms.clear();
}
