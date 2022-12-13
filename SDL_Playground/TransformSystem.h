#pragma once
#include <vector>
struct Float2;
struct Transform;


class TransformSystem
{
    std::vector<Transform> transforms;
    
public:
    void Update();
    int Register(int EntityID, Float2 position, Float2 size);
    void Unregister(int transformID);
    void Destructor();
    Transform* GetTransform(int id);
    
};
