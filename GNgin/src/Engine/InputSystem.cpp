#include "InputSystem.h"
#include <SDL_events.h>


void InputSystem::Reset()
{
    Esc = 0;
    W = 0;
    S = 0;
    A = 0;
    D = 0;
    Space = 0;
}

void InputSystem::Update()
{
    Reset();
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) { Esc = true; }
        if (event.type == SDL_KEYDOWN &&
            event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            Space = 1;
        }
    }

    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if (keyStates[SDL_SCANCODE_ESCAPE]) { Esc = 1; }
    if (keyStates[SDL_SCANCODE_W]) { W = 1; }
    if (keyStates[SDL_SCANCODE_S]) { S = 1; }
    if (keyStates[SDL_SCANCODE_A]) { A = 1; }
    if (keyStates[SDL_SCANCODE_D]) { D = 1; }
}
