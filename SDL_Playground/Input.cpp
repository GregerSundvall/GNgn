#include "Input.h"

#include <SDL_events.h>


void Input::Reset()
{
    Esc = 0;
    W = 0;
    S = 0;
    A = 0;
    D = 0;
}

void Input::Update()
{
    Reset();
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { Esc = true; } }

    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    if (keyStates[SDL_SCANCODE_ESCAPE]) { Esc = 1; }
    if (keyStates[SDL_SCANCODE_W]) { W = 1; }
    if (keyStates[SDL_SCANCODE_S]) { S = 1; }
    if (keyStates[SDL_SCANCODE_A]) { A = 1; }
    if (keyStates[SDL_SCANCODE_D]) { D = 1; }
}
