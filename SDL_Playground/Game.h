#pragma once
#include <SDL_rect.h>

#include "EntitySystem.h"

class DrawSystem
{
    std::vector<SDL_Rect> Rectangles;

    void AddRectangle(SDL_Rect rect){};
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
