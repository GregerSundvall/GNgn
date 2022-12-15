#pragma once
#include <vector>
#include "Components.h"

class DrawSystem
{
    std::vector<DrawObject> objectsToDraw;

public:
    DrawSystem()
    {
        objectsToDraw.reserve(1000);
    }
    
    void Add(Float2 position, Float2 size, Sprite sprite);
    void DrawAll();
    void Draw(DrawObject& drawObject);

};
