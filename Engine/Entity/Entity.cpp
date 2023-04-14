#include "Entity.h"

#include "Entities.h"
#include "TransformSystem.h"
#include "../Engine.h"
#include "../Graphics/Graphics.h"


Entity::Entity(double x, double y, double width, double height, double mass, const char* filePath) {
	rigidBody = Physics::Create(x, y, width, height, mass);
	texture = Graphics::AddTexture(filePath);
}

// void Entity::Update(double deltaTime) {}

//
// void Entity::SetPosition(Vector2 const position) {
// 	this->position = position;
// }
// void Entity::SetPosition(double x, double y) {
// 	position = {x, y};
// }
// void Entity::SetRotation(double const rotation) {
// 	this->rotation = rotation;
// }
// void Entity::SetMass(double const weight) {
// 	mass = weight;
// }
// void Entity::SetTexture(const char* filePath) {
// 	texture = Graphics::AddTexture(filePath);
// }
//
//
// void Entity::SetShape(double const width, double const height) {
// 	Physics::Create(width, height);
// }
// void Entity::SetShape(double const radius) {
// 	Physics::Create(radius);
// }
// void Entity::SetBoxWidth(double const width) {
// 	if (shape->GetType() == BOX)
// 		shape->SetBoxWidth(width);
// }
// void Entity::SetBoxHeight(double const height) {
// 	if (shape->GetType() == BOX)
// 		shape->SetBoxHeight(height);
// }
// void Entity::SetDiameter(double const diameter) {
// 	if (shape->GetType() == CIRCLE)
// 		shape->SetRadius(diameter * 0.5);
// }
//
//
// Vector2 Entity::GetPosition() { return rigidBody->position; }
// double Entity::GetRotation() { return rigidBody->rotation; }
// double Entity::GetMass() { return rigidBody->mass; }
// ShapeType Entity::GetShapeType() { return rigidBody->GetShapeType(); }
//
// Vector2 Entity::GetBoxSize() {
// 	if (shape->GetType() == BOX) 
// 		return shape->GetBoxSize();
// 	return Vector2();
// }
// double Entity::GetDiameter() {
// 	if (shape->GetType() == CIRCLE)
// 		return shape->GetRadius() * 2;
// 	return 0;
// }
//
