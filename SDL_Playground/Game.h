#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

#include "Engine.h"
#include "EntitySystem.h"

struct DrawObject
{
    Sprite sprite;
    SDL_Rect rect;
};
class DrawSystem
{
    std::vector<DrawObject> objectsToDraw;

public:
    DrawSystem()
    {
        objectsToDraw.reserve(1000);
    }
    void Add(Float2 position, Float2 size, Sprite sprite)
    {
        SDL_Rect rect = {static_cast<int>(position.x - size.x * 0.5),
                        static_cast<int>(position.y - size.y * 0.5),
                        static_cast<int>(size.x), static_cast<int>(size.y)};
        objectsToDraw.push_back(DrawObject(sprite, rect));
    }
    void DrawAll()
    {
        for (int i = 0; i < objectsToDraw.size(); ++i)
        {
            Draw(objectsToDraw[i]);
        }
        objectsToDraw.clear();
    }
    void Draw(DrawObject& drawObject)
    {
        SDL_SetRenderDrawColor(renderer, drawObject.sprite.Color.R,
            drawObject.sprite.Color.G,
            drawObject.sprite.Color.B,
            drawObject.sprite.Color.A);
        SDL_RenderFillRect(renderer, &drawObject.rect);
    }
};

class Game
{
    bool isRunning = true;
    int PlayerEntityID;
    int EnemiesToSpawn = 100;
    std::vector<int> EnemyEntityIDs;

    
    EntitySystem* entitySystem = new EntitySystem;
    DrawSystem* drawSystem = new DrawSystem;
    // Event system
    // Move input system here?
    // Move SDL stuff here?
    // Move all in this class to main?

public:

    void Start();
    void SpawnEnemy();
    void Update();
    void Destroy();
};
