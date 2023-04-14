#include "Input.h"

#include <SDL_events.h>

#include "Engine.h"

void Input::Init()
{
	keyStates = SDL_GetKeyboardState(NULL);
}

void Input::Update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) 
	{
		switch(event.type)
		{
		case SDL_QUIT:
			{
				Engine::Stop();
				break;
			}
		case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
					Engine::Stop();
				break;
			}
		default: {};
		}

		
	}
}



bool Input::KeyIsDown(int const key) {
	return keyStates[key];
}

bool Input::KeyWasPressed(int key) { return false; } // TODO not implemented
bool Input::KeyWasReleased(int key) { return false; } // TODO not implemented
