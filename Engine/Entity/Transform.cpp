#include "Transform.h"



Transform::Transform(Vector2 const position, double const rotation, Vector2 const size) {
	this->position = position;
	this->rotation = rotation;
	this->size = size;
}

void Transform::SetPosition(Vector2 const position) {
	this->position = position;
}

Vector2 Transform::GetPosition() const {
	return position;
}

void Transform::SetRotation(double const rotation) {
	this->rotation = rotation;
}
double Transform::GetRotation() const {
	return rotation;
}

void Transform::SetSize(Vector2 const size) {
	this->size = size;
}
Vector2 Transform::GetSize() const {
	return size;
}
