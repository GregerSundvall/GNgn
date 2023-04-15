#include "Entity.h"

#include "../Engine.h"
#include "../Graphics/Graphics.h"


Entity::Entity(const double x, const double y, const double width, const double height, const double mass, const char* filePath) {
	rigidBody = Physics::Create(x, y, width, height, mass);
	texture = Graphics::AddTexture(filePath);
}

// void Entity::Update(double deltaTime) {}
