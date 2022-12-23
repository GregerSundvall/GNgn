#pragma once
#include <vector>
struct Color;
struct Sprite;
class EntitySystem;


class SpriteSystem
{
    std::vector<Sprite> sprites;
    
public:
    SpriteSystem();
    
    int Register(int entityID, Color color);
    void Unregister(int spriteID);
    void AssignNewEntityID(int spriteID, int newEntityID);
    void Update();
    void Destructor() {sprites.clear();}
};
