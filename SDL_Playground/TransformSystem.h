#pragma once
#include <vector>


struct Vector2;
struct Transform;

class TransformSystem
{
    std::vector<Transform> transforms;
    std::vector<int> recycledIndexes;
    int memberCount = 0;
    int nextFreshIndex = 0;

public:
    void Update();
    int Register(Vector2 position, Vector2 velocity);
    void Unregister(int id);
    void Destroy();
    
};
