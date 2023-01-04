#pragma once
#include <random>
#include <SDL.h>
#include "DrawSystem.h"
#include "EntitySystem.h"
#include "Input.h"
class Game;


extern DrawSystem* drawSystem;
extern Input* input;
extern Game* game;
extern EntitySystem* entitySystem;
extern std::default_random_engine generator;
extern float dTime;

class Engine
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    const int width = 800;
    const int height = 1000;
    bool SDLisRunning = true;

public:
    Engine();
    void Run();
    SDL_Renderer* GetRenderer();
};
