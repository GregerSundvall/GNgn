#include "TransformSystem.h"

#include "Engine.h"
#include "Transform.h"

void TransformSystem::Update()
{
    // Take any "empties" in array into account when looping
    int maxIndex = memberCount + recycledIndexes.size();

    // Update positions
    for (int i = 0; i < maxIndex; ++i)
    {
        // If index is not in use, skip.
        if (transforms[i].ID == -1)  { continue;  }
        
        transforms[i].Position.X += transforms[i].Velocity.X * dTime;   
        transforms[i].Position.Y += transforms[i].Velocity.Y * dTime;  
    }

    // Let Game handle entity going out of bounds
}

int TransformSystem::Register(Vector2 position, Vector2 velocity)
{
    int index;
    
    if (recycledIndexes.size() > 0) // Recycled index available, use that.
    {
        index = recycledIndexes.back();
        recycledIndexes.pop_back();
    }
    else  // No recycled indexes available, use a fresh index.
    {
        index = nextFreshIndex;
        nextFreshIndex++;
    }
    transforms[index] = Transform(position, velocity);
    transforms[index].ID = index; // Let transform know it's own index. Needed?
    memberCount++;
    
    return index;
}

void TransformSystem::Unregister(int id)
{
    transforms[id] = Transform(); // Clear data at index
    recycledIndexes.push_back(id); // Make index available for reuse
    memberCount--;
}

void TransformSystem::Destroy()
{
    transforms.clear();
    recycledIndexes.clear();
}
