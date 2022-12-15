#include "SpriteSystem.h"

int SpriteSystem::Register(int entityID, Color color)
{
    sprites.push_back(Sprite(entityID, color));
    return static_cast<int>(sprites.size()) -1;
}

void SpriteSystem::Unregister(int spriteID)
{
    sprites[spriteID] = sprites[sprites.size() -1];
    sprites.pop_back();
}
