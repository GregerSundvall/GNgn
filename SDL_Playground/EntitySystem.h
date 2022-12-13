#pragma once
#include "CollisionSystem.h"
#include "Components.h"
#include "TransformSystem.h"
struct Collider;
struct Transform;




struct Entity
{
    int ID;
    int TransformID = -1;
    int MovementID = -1;
    int CollisionID = -1;
    int SpriteID = -1;
};

class MovementSystem
{
    std::vector<Movement> movements;

public:
    int Register(int entityID, Float2 size)
    {
        movements.push_back(Movement(entityID, size));
        return movements.size() -1;
    }
    void Unregister(int spriteID)
    {
        movements[spriteID] = movements[movements.size() -1];
        movements.pop_back();
    }
    void Update(){}
};

class SpriteSystem
{
    std::vector<Sprite> sprites;
public:
    int Register(int entityID, Color color)
    {
        sprites.push_back(Sprite(entityID, color));
        return sprites.size() -1;
    }
    void Unregister(int spriteID)
    {
        sprites[spriteID] = sprites[sprites.size() -1];
        sprites.pop_back();
    }
};


class EntitySystem
{
    std::vector<Entity> entities;
    std::vector<int> recycledIndexes;
    int memberCount = 0;
    int nextFreshIndex = 0;
    
    TransformSystem* transformSystem = new TransformSystem;
    CollisionSystem* collisionSystem = new CollisionSystem;
    MovementSystem* movementSystem = new MovementSystem;
    SpriteSystem* spriteSystem = new SpriteSystem;
    
public:

    int CreateEntity(Float2 position, bool addTransform = true,
        bool addCollider = true, Float2 size = Float2(4, 4));
    void DestroyEntity(int entityID);
    void AddTransform(int entityID, Float2 position, Float2 size);
    void AddCollider(int entityID);
    void AddMovement(int entityID, Float2 velocity);
    void AddSprite(int entityID, Color color);
    void RemoveTransform(int entityID);
    void RemoveCollider(int entityID);
    void RemoveMovement(int entityID);
    void RemoveSprite(int entityID);
    void Update();
    void Destructor();
};






