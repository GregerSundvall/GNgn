#pragma once
#include <vector>

#include "../Misc/Vector2.h"


class Entity;


static std::vector<Entity> entities;
static std::vector<int> freeSlots;

class EntitySystem
{
public:
	void Init();
	void Update();
	
	static int CreateEntity();
	static void DestroyEntity(const int entityID);
	static void SetPosition(int entityID, double posX, double posY);
	
};
