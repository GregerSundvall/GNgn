#pragma once
#include <set>
#include <vector>
#include "Components.h"
#include "TransformSystem.h"
// class TransformSystem;
class CollisionSystem;
class MovementSystem;
class SpriteSystem;
class DrawSystem;
class Game;
// struct Collider;
// struct Transform;



class EntitySystem
{
    std::vector<Entity> entities;
    // std::set<int> collidingIDs;
    
    TransformSystem* transformSystem;
    CollisionSystem* collisionSystem;
    MovementSystem* movementSystem;
    SpriteSystem* spriteSystem;
    DrawSystem* drawSystem; // Being forwarded to spritesystem in constructor. May not need to save?
    Game* game;
    //InputSystem
    //HealthSystem
    //ScoreSystem?
    
public:
    EntitySystem(DrawSystem* drawSystem, Game* game);
    int CreateEntity();
    Entity* GetEntity(int entityID) { return &entities[entityID]; }
    Float2* GetPosition(int entityID) { return transformSystem->GetPosition(entities[entityID].transformID); }
    Transform* GetTransform(int entityID) { return transformSystem->GetTransform(entities[entityID].transformID); }
    void SetVelocity(int entityID, Float2 velocity);
    void AddOffset(int entityID, Float2 velocity);
    void Move(int entityID, Float2 offset);
    void MoveTo(int entityID, Float2 position);
    void DestroyEntity(int entityID);
    void NotifyOverlap(std::vector<int> collidingEntities);
    void UpdateTransformID(int eID, int newTransformID) { entities[eID].transformID = newTransformID; }
    void UpdateMovementID(int eID, int newMovementID)   { entities[eID].movementID = newMovementID; }
    void UpdateColliderID(int eID, int newColliderID)   { entities[eID].collisionID = newColliderID; }
    void UpdateSpriteID(int eID, int newSpriteID)       { entities[eID].spriteID = newSpriteID; }
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








