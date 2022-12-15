#pragma once
#include <vector>

#include "Components.h"
#include "DrawSystem.h"
#include "EntitySystem.h"

struct Color;

class SpriteSystem
{
    std::vector<Sprite> sprites;
    EntitySystem* entitySystem;
    DrawSystem* drawSystem;
public:
    SpriteSystem(EntitySystem* entitySystem, DrawSystem* drawSystem);
    int Register(int entityID, Color color);
    void Unregister(int spriteID);
    void Update();
    void Destructor() {sprites.clear();}
};
