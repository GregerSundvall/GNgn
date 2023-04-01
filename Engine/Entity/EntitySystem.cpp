#include "EntitySystem.h"

#include "Entity.h"
#include "TransformSystem.h"


void EntitySystem::Init() {
	entities = {};
	freeSlots = {};
}

void EntitySystem::Update() {
	
}
int EntitySystem::CreateEntity() {
	entities.push_back(Entity());
	return entities.size() -1;
}
void EntitySystem::DestroyEntity(const int entityID) {
	freeSlots.push_back(entityID);
	entities.at(entityID) = Entity();
}

void EntitySystem::SetPosition(int entityID, double posX, double posY) {}


