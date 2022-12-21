#pragma once
#include <vector>
#include "Components.h"
#include "DrawSystem.h"
struct Color;
class EntitySystem;


class SpriteSystem
{
    std::vector<Sprite> sprites;
    EntitySystem* entitySystem;
    DrawSystem* drawSystem;
    
public:
    SpriteSystem(EntitySystem* entitySystem, DrawSystem* drawSystem);
    
    int Register(int entityID, Color color);
    void Unregister(int spriteID);
    void AssignNewEntityID(int spriteID, int newEntityID);
    void Update();
    void Destructor() {sprites.clear();}
};
