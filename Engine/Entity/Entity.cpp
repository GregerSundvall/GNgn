#include "Entity.h"

#include "../Engine.h"
#include "../Graphics/Graphics.h"


Entity::Entity(double x, double y, double width, double height, double mass, const char* filePath) {
	rigidBody = Physics::Create(x, y, width, height, mass);
	texture = Graphics::AddTexture(filePath);
}

// void Entity::Update(double deltaTime) {}
