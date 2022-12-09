#pragma once
#include "Collision.h"
#include "TransformSystem.h"
struct Collider;
struct Transform;


struct Color
{
    int R, G, B;
    int A = 255;
};

struct Entity
{
    int ID;
    int TransformID = -1;
    int CollisionID = -1;
    Color Color = {100, 100, 100};
};



class EntitySystem
{
    std::vector<Entity> entities;
    std::vector<int> recycledIndexes;
    int memberCount = 0;
    int nextFreshIndex = 0;
    
    TransformSystem* transformSystem = new TransformSystem;
    CollisionSystem* collisionSystem = new CollisionSystem;
    
public:

    int CreateEntity(Float2 position, bool addTransform = true,
        bool addCollider = true, Float2 size = Float2(4, 4));
    void AddTransform(int entityID, Float2 position, Float2 size);
    void AddCollider(int entityID);
    void Update();
    void Destroy();
};
