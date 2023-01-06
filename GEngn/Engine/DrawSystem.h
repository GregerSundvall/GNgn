#pragma once
#include <map>
#include <SDL_render.h>
#include <string>
#include <vector>
#include "Components.h"

class DrawSystem
{
    std::vector<DrawObject> objectsToDraw;
    std::vector<DrawObject> lvl0StuffToDraw; // Background objects
    std::vector<DrawObject> lvl1StuffToDraw; // Enemies?
    std::vector<DrawObject> lvl2StuffToDraw; // Player?
    std::vector<DrawObject> lvl3StuffToDraw; // UI

    std::map<std::string, SDL_Texture*> textureCache;

    

public:
    DrawSystem(SDL_Renderer* renderer)
    {
        objectsToDraw.reserve(1000);
        this->renderer = renderer;
    }
    
    SDL_Renderer* renderer;
    void Add(Float2 position, Float2 size, Sprite& sprite);
    void CacheTexture(std::string imagePath);
    void CacheTexture(std::string text, std::string fontPath);
    void Update();
    void Draw(DrawObject& drawObject);
};
