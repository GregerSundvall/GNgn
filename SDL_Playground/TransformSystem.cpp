#include "TransformSystem.h"
#include "Engine.h"
#include "Components.h"

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
    transforms[transformID] = transforms[transforms.size() -1];
    transforms.pop_back();
}

Float2* TransformSystem::GetPosition(int transformID)
{
    return &transforms[transformID].Position;
}

Transform* TransformSystem::GetTransform(int transformID)
{
    return &transforms[transformID];
}

void TransformSystem::Destructor()
{
    transforms.clear();
}
