#pragma once
#include "Collision.h"
#include "TransformSystem.h"
struct Collider;
struct Transform;


struct Color
{
    int R;
    int G;
    int B;
    int A = 255;
};

struct Entity
{
    int ID;
    int TransformID = -1;
    int ColliderID = -1;
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

    int CreateEntity();
    void Update();
    void Destroy();
};
