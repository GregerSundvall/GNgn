#include "../Engine.h"
#include "SpriteSystem.h"
#include "EntitySystem.h"


SpriteSystem::SpriteSystem(EntitySystem* entitySystem)
{
    this->entitySystem = entitySystem;
}

int SpriteSystem::Register(int entityID, int textureID) // Returns a spriteID
{
    sprites.push_back(Sprite(entityID, textureID));
    return static_cast<int>(sprites.size()) -1;
}

void SpriteSystem::Unregister(int spriteID) 
{
    if (spriteID < sprites.size() -1)
    {
        entitySystem->UpdateSpriteID(sprites[sprites.size() -1].entityID, spriteID);
        sprites[spriteID].entityID = sprites[sprites.size() - 1].entityID;
        sprites[spriteID].textureID = sprites[sprites.size() - 1].textureID;
        sprites[spriteID].color = sprites[sprites.size() -1].color;
    }
    sprites.pop_back();
}

void SpriteSystem::SetColor(int spriteID, Color color)
{
    sprites[spriteID].color = color;
}


void SpriteSystem::SetTexture(int spriteID, int textureID)
{
    sprites[spriteID].textureID = textureID;
}

void SpriteSystem::SetTexture(int spriteID, const std::string& text, const std::string& fontPath) // Create and assign texture from text.
{
    sprites[spriteID].text = text;
    sprites[spriteID].fontPath = fontPath;
    sprites[spriteID].color = {0, 100, 100, 255};
    drawSystem->CacheTexture(text, fontPath);
}

void SpriteSystem::AssignNewEntityID(int spriteID, int newEntityID) //Used when destroying an entity
{
    sprites[spriteID].entityID = newEntityID;
}

void SpriteSystem::Update()
{
    for (int i = 0; i < sprites.size(); ++i)
    {
        auto tf = entitySystem->GetTransform(sprites[i].entityID);
        drawSystem->Add(tf->position, tf->size, sprites[i]);
    }
}
