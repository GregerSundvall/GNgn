#pragma once
#include <vector>
#include "Components.h"

class DrawSystem
{
    std::vector<DrawObject> objectsToDraw;
    // Split to two or three vectors, for Z prioritization?

public:
    DrawSystem()
    {
        objectsToDraw.reserve(1000);
    }
    
    void Add(Float2 position, Float2 size, Sprite sprite);
    void DrawAll();
    void Draw(DrawObject& drawObject);

};
