#pragma once
#include <SDL_render.h>
#include <vector>
#include "Components.h"

class DrawSystem
{
    std::vector<DrawObject> objectsToDraw;
    SDL_Renderer* renderer;
    // Split to two or three vectors, for Z prioritization?

public:
    DrawSystem(SDL_Renderer* renderer)
    {
        objectsToDraw.reserve(1000);
        this->renderer = renderer;
    }
    
    void Add(Float2 position, Float2 size, Sprite sprite);
    void DrawAll();
    void Draw(DrawObject& drawObject);

};
