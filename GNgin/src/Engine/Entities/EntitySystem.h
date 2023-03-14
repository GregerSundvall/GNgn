#pragma once
#include <string>
#include <vector>
#include "../Misc/Components.h"
#include "TransformSystem.h"
class Engine;
class CollisionSystem;
class MovementSystem;
class SpriteSystem;


class EntitySystem
{
    std::vector<Entity> entities;

    Engine* engine;
    TransformSystem* transformSystem;
    CollisionSystem* collisionSystem;
    MovementSystem* movementSystem;
    SpriteSystem* spriteSystem;
    
public:
    EntitySystem(Engine* engine);
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
    void AddSprite(int entityID, Color color); // Set color sprite
    void AddSprite(int entityID, int textureID); // Add sprite component and set sprite.
    void AddSprite(int entityID, std::string text, std::string font); // Set text sprite
    void RemoveTransform(int entityID);
    void RemoveCollider(int entityID);
    void RemoveMovement(int entityID);
    void RemoveSprite(int entityID);
    void Update();
};








