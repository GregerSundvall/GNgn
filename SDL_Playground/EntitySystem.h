#pragma once
#include "Components.h"
#include "CollisionSystem.h"
#include "MovementSystem.h"
#include "TransformSystem.h"
struct Collider;
struct Transform;



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
    void Destructor() {sprites.clear();}
};


class EntitySystem
{
    std::vector<Entity> entities;
    
    TransformSystem* transformSystem = new TransformSystem;
    CollisionSystem* collisionSystem = new CollisionSystem;
    MovementSystem* movementSystem = new MovementSystem(&this);
    SpriteSystem* spriteSystem = new SpriteSystem;
    
public:

    int CreateEntity();
    Entity* GetEntity(int entityID) {return &entities[entityID];}
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






