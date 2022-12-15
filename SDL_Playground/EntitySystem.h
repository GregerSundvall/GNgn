#pragma once
#include "Components.h"
#include "CollisionSystem.h"
#include "MovementSystem.h"
#include "SpriteSystem.h"
#include "TransformSystem.h"
struct Collider;
struct Transform;




class EntitySystem
{
    std::vector<Entity> entities;
    
    TransformSystem* transformSystem = new TransformSystem;
    CollisionSystem* collisionSystem = new CollisionSystem(this);
    MovementSystem* movementSystem = new MovementSystem(this);
    SpriteSystem* spriteSystem = new SpriteSystem;
public:
    

    int CreateEntity();
    Entity* GetEntity(int entityID) {return &entities[entityID];}
    void Move(int entityID, Float2 offset);
    void MoveTo(int entityID, Float2 position);
    void SweepAndMove(int entityID, Float2 offset);
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








