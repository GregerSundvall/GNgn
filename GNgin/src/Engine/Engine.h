#pragma once
#include <random>
#include <SDL.h>
#include "Graphics/DrawSystem.h"
#include "Graphics/Graphics.h"
#include "Entities/EntitySystem.h"
#include "Input/InputSystem.h"
class Game;


extern DrawSystem* drawSystem;
extern InputSystem* input;
extern Game* game;
extern EntitySystem* entitySystem;
extern std::default_random_engine generator;
extern float dTime;

class Engine
{
    GraphicsSystem* graphics;
    SDL_Renderer* renderer;
    SDL_Window* window;
    const int width = 800;
    const int height = 1000;
    bool isRunning = true;

    //TODO Event system
    
    // Framerate stuff
    int frameRate = 0;
    Uint64 previousTicks = SDL_GetPerformanceCounter();
    float FPScounts[100] = {0};
    int nextFPSIndex = 0;
    float accumulatedFPS = 0;
    
    void CalculateFPS();
    void MainLoop();
    
public:
    Engine();
    int FrameRate();
};
