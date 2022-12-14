#pragma once
#include <vector>

#include "Components.h"
struct Float2;
struct Transform;


class TransformSystem
{
    std::vector<Transform> transforms;
    
public:
    void Update();
    int Register(int EntityID, Float2 position, Float2 size);
    void Unregister(int transformID);
    Transform* GetPosition(int id);
    void SetPosition(int transformID, Float2 position) {transforms[transformID].Position = position;}
    void AddOffset(int transformID, Float2 offset) {transforms[transformID].Position += offset;}
    void Destructor();
    
};
