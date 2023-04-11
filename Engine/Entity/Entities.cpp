#include "Entities.h"

#include <iostream>

#include "TransformSystem.h"
#include "../Physics/Physics.h"
// #include "../Graphics/Graphics.h"


void Entities::Init() {
	boxEntities.reserve(1000);
	TransformSystem::Init();
}

void Entities::CreateBoxEntity(double x, double y, double width, double height, double weight, const char* filePath) {
	Entity new = Entity( )
}

// void Entities::CreateCircleEntity(double x, double y, double radius, double weight, const char* filePath) {
// 	
// }


void Entities::Update() {
	
}

int Entities::EntityCount() { return entities.size(); }

Entity* Entities::CreateEntity() {
	entities.emplace_back(Entity(entities.size()));
	return &entities.at((int)entities.size() -1);
}

Entity* Entities::CreateEntity(double const x, double const y, double const width, double const height,
                                   const char* imageFilePath, bool physics) {
	
	entities.emplace_back(Entity(entities.size(), x, y, width, height, imageFilePath));
	return &entities.at(entities.size() -1);
}

void Entities::DestroyEntity(int const entityID) {
	freeSlots.push_back(entityID);
	entities.at(entityID) = Entity(-1);
}

Vector2 Entities::GetPosition(int entityID) {
	return TransformSystem::GetPosition(entities.at(entityID).GetTransformID());
}
void Entities::SetPosition(int const entityID, Vector2 const& position) {
	entities.at(entityID).SetPosition(position,);
}

double Entities::GetRotation(int const entityID) {
	return TransformSystem::GetRotation(entities.at(entityID).GetTransformID());
}
void Entities::SetRotation(int const entityID, double rotation) {
	TransformSystem::SetRotation(entities.at(entityID).GetTransformID(), rotation);
}

Vector2 Entities::GetSize(int const entityID) {
	return TransformSystem::GetSize(entities.at(entityID).GetTransformID());
}
void Entities::SetSize(int const entityID, double width, double height) {
	entities.at(entityID).SetSize({width, height});
}
void Entities::SetSize(int const entityID, Vector2 const size) {
	entities.at(entityID).SetSize(size);
}

void Entities::SetTexture(int const entityID, const char* filePath) {
	entities.at(entityID).SetTexture(filePath);
}

int Entities::EnablePhysics(int entityID) {
	return Physics::Create();
}

std::vector<Sprite>* Entities::GetSprites() {
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














