#include "Transform.h"


Transform::Transform(Vector2 const position, double const rotation, Vector2 const scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Vector2& Transform::GetPosition() {
	return position;
}
