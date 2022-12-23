#pragma once
#include <random>
#include <SDL.h>
#include "DrawSystem.h"
#include "EntitySystem.h"
class Game;
#include "Input.h"


extern DrawSystem* drawSystem;
extern Input* input;
extern Game* game;
extern EntitySystem* entitySystem;
extern std::default_random_engine generator;
extern float dTime;

class Engine
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    const int width = 800;
    const int height = 1000;
    bool SDLisRunning = true;

public:
    Engine();
    void Run();
};
