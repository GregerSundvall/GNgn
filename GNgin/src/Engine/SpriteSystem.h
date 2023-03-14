#pragma once
#include <vector>
struct Color;
struct Sprite;
class EntitySystem;


class SpriteSystem
{
    std::vector<Sprite> sprites;
    EntitySystem* entitySystem;
    
public:
    SpriteSystem(EntitySystem* entitySystem);
    
    int Register(int entityID, Color color);
    void Unregister(int spriteID);
    void SetColor(int spriteID, Color color);
    void SetTexture(int spriteID, std::string imagePath);
    void SetTexture(int spriteID, const std::string &text, const std::string &fontPath);
    void AssignNewEntityID(int spriteID, int newEntityID);
    void Update();
};
