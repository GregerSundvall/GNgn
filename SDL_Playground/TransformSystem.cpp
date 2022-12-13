#include "TransformSystem.h"
#include "Engine.h"
#include "Components.h"

void TransformSystem::Update()
{
    // Update positions
    for (int i = 0; i < transforms.size(); ++i)
    {
        // If index is not in use, skip.
        // if (transforms[i].ID == -1)  { continue;  }
        //
        // transforms[i].Position.X += transforms[i].Velocity.X * dTime;   
        // transforms[i].Position.Y += transforms[i].Velocity.Y * dTime;  
    }

    // Let Game handle entity going out of bounds?
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

void TransformSystem::Destructor()
{
    transforms.clear();
}

Transform* TransformSystem::GetTransform(int id)
{
    return &transforms[id];
}
