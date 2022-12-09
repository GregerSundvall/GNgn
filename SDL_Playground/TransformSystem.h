#pragma once
#include <vector>
struct Float2;
struct Transform;


class TransformSystem
{
    std::vector<Transform> transforms;
    std::vector<int> recycledIndexes;
    int memberCount = 0;
    int nextFreshIndex = 0;
    
public:
    void Update();
    int Register(Float2 position, Float2 size);
    void Unregister(int id);
    void Destroy();
    Transform* GetTransform(int id);
    
};
