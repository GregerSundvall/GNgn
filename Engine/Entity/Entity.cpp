#include "Entity.h"

#include "EntitySystem.h"
#include "TransformSystem.h"
#include "../Graphics/Graphics.h"


Entity::Entity(int const entityID) {
	this->entityID = entityID;
}

Entity::Entity(int const entityID, double x, double y, double width, double height, const char* filePath) {
	this->entityID = entityID;
	SetPosition({x, y});
	SetSize({width, height});
	SetTexture(filePath);
}

void Entity::Update(double deltaTime) {}

Vector2 Entity::GetPosition() {
	if (transformID == -1) { transformID = TransformSystem::Create(); }
	return TransformSystem::GetPosition(transformID);
}

void Entity::SetPosition(Vector2 const position) {
	if (transformID == -1) { transformID = TransformSystem::Create(position);
		return; }
	TransformSystem::SetPosition(transformID, position);
}

double Entity::GetRotation() {
	if (transformID == -1) { transformID = TransformSystem::Create(); }
	return TransformSystem::GetRotation(transformID);
}
void Entity::SetRotation(double const rotation) {
	if (transformID == -1) { transformID = TransformSystem::Create({0, 0}, rotation);
		return; }
	TransformSystem::SetRotation(transformID, rotation);
}

Vector2 Entity::GetSize() {
	if (transformID == -1) { transformID = TransformSystem::Create(); }
	return TransformSystem::GetSize(transformID);
}
void Entity::SetSize(Vector2 const size) {
	if (transformID == -1) { transformID = TransformSystem::Create({0, 0}, 0, size);
		return; }
	TransformSystem::SetSize(transformID, size);
}

void Entity::SetTexture(const char* filePath) {
	textureID = Graphics::AddTexture(filePath);
}

int Entity::GetEntityID() const { return entityID; }
int Entity::GetTransformID() const { return transformID; }
int Entity::GetRigidBodyID() const { return rigidBodyID; }
int Entity::GetTextureID() const { return textureID; }
