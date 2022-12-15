#pragma once
#include <vector>

#include "Components.h"

struct Color;

class SpriteSystem
{
    std::vector<Sprite> sprites;
public:
    int Register(int entityID, Color color);
    void Unregister(int spriteID);
    void Destructor() {sprites.clear();}
};
