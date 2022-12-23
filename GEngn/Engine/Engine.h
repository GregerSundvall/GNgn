#pragma once
#include <random>
#include <SDL.h>
#include "Input.h"
class Game;


extern SDL_Renderer* renderer;
extern Input* input;
extern float dTime;
extern std::default_random_engine generator;

class Engine
{
    SDL_Window* window;
    Game* game;
    const int width = 800;
    const int height = 1000;
    bool SDLisRunning = true;

public:
    Engine();
    void Run();
};
