#include "EntitySystem.h"

#include <iostream>

#include "TransformSystem.h"
#include "../Physics/Physics.h"
// #include "../Graphics/Graphics.h"


void EntitySystem::Init() {
	entities.reserve(1000);
	freeSlots.reserve(1000);
	TransformSystem::Init();
}

void EntitySystem::CreateBoxEntity(double x, double y, double width, double height, double weight, const char* filePath) {
	
}

void EntitySystem::CreateCircleEntity(double x, double y, double radius, double weight, const char* filePath) {
	
}


void EntitySystem::Update() {
	
}

int EntitySystem::EntityCount() { return entities.size(); }

Entity* EntitySystem::CreateEntity() {
	entities.emplace_back(Entity(entities.size()));
	return &entities.at((int)entities.size() -1);
}

Entity* EntitySystem::CreateEntity(double const x, double const y, double const width, double const height,
                                   const char* imageFilePath, bool physics) {
	
	entities.emplace_back(Entity(entities.size(), x, y, width, height, imageFilePath));
	return &entities.at(entities.size() -1);
}

void EntitySystem::DestroyEntity(int const entityID) {
	freeSlots.push_back(entityID);
	entities.at(entityID) = Entity(-1);
}

Vector2 EntitySystem::GetPosition(int entityID) {
	return TransformSystem::GetPosition(entities.at(entityID).GetTransformID());
}
void EntitySystem::SetPosition(int const entityID, Vector2 const& position) {
	entities.at(entityID).SetPosition(position,);
}

double EntitySystem::GetRotation(int const entityID) {
	return TransformSystem::GetRotation(entities.at(entityID).GetTransformID());
}
void EntitySystem::SetRotation(int const entityID, double rotation) {
	TransformSystem::SetRotation(entities.at(entityID).GetTransformID(), rotation);
}

Vector2 EntitySystem::GetSize(int const entityID) {
	return TransformSystem::GetSize(entities.at(entityID).GetTransformID());
}
void EntitySystem::SetSize(int const entityID, double width, double height) {
	entities.at(entityID).SetSize({width, height});
}
void EntitySystem::SetSize(int const entityID, Vector2 const size) {
	entities.at(entityID).SetSize(size);
}

void EntitySystem::SetTexture(int const entityID, const char* filePath) {
	entities.at(entityID).SetTexture(filePath);
}

int EntitySystem::EnablePhysics(int entityID) {
	return Physics::Create();
}

std::vector<Sprite>* EntitySystem::GetSprites() {
	std::vector<Sprite>* sprites = new std::vector<Sprite>;
	sprites->reserve(entities.size());
	
	for (int i = 0; i < entities.size(); ++i) {
		Entity entity = entities.at(i);
		if (entity.GetRigidBodyID() == -1 ||  // Entity does not have a transform
			entity.GetTextureID() == -1) // Entity does not have a texture.
			continue;
		// TODO If outside screen: continue. Maybe..?
		
		sprites->emplace_back(Sprite(entity.GetTextureID(),
			*Physics::GetPosition(entity.GetTransformID()),
			Physics::GetRotation(entity.GetTransformID())));
	}
	return sprites;
}














