#pragma once

#include "../Misc/Misc.h"
#include "../Physics/RigidBody.h"



class Entity
{
		
public:
	RigidBody* rigidBody;
	SDL_Texture* texture;

	// Creates a box entity
	Entity(double x, double y, double width, double height, double mass, const char* filePath);
	
	// virtual void Update(double deltaTime);
};


