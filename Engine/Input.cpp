#include "Input.h"

#include <SDL_events.h>

void Input::Update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) 
	{
		switch(event.type)
		{
		case SDL_QUIT:
			{
				// running = false;
				break;
			}
		case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
					// running = false;
				break;
			}
		default: {};
		}
	}
}
