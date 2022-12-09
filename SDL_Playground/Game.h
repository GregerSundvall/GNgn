#pragma once
#include "EntitySystem.h"


class Game
{
    bool isRunning = true;
    EntitySystem* entitySystem = new EntitySystem;
    // Move input system here?
    // Event system

public:

    void Update();
    void Destroy();
};
