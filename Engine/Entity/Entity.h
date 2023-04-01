#pragma once
#include <vector>

#include "../Misc/Vector2.h"


class Entity
{
	int entityID = -1;
	int transformID = -1;
	int physicsID = -1; 
	int graphicsID = -1;
public:
	Vector2& GetPosition();
	
};


