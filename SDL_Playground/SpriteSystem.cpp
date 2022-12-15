#include "SpriteSystem.h"

SpriteSystem::SpriteSystem(EntitySystem* entitySystem, DrawSystem* drawSystem)
{
    this->entitySystem = entitySystem;
    this->drawSystem = drawSystem;
}

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

void SpriteSystem::Update()
{
    for (int i = 0; i < sprites.size(); ++i)
    {
        auto tf = entitySystem->GetTransform(sprites[i].entityID);
        drawSystem->Add(tf->Position, tf->Size, sprites[i]);
    }
}
