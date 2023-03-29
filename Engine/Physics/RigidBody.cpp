#include "RigidBody.h"

#include <SDL_image.h>

#include "../Graphics/Graphics.h"


RigidBody::RigidBody(const Shape& shape, double x, double y, double mass) {
	this->shape = shape.Clone();
	this->position = Vector2(x, y);
	this->velocity = Vector2(0, 0);
	this->acceleration = Vector2(0,0);
	this->rotation = 0.0;
	this->angularVelocity = 0.0;
	this->angularAcceleration = 0.0;
	this->sumOfForces = Vector2(0, 0);
	this->sumOfTorque = 0.0;
	this->restitution = 0.6;
	this->friction = 0.7;
	this->mass = mass;

	if (mass != 0.0) {
		this->inverseMass = 1.0 / mass;
	}
	else {
		this->inverseMass = 0.0;
	}

	 momentOfInertia = shape.GetMomentOfInertia() * mass;
	if ( momentOfInertia != 0.0) {
		this->inverseMomentOfInertia = 1.0 / momentOfInertia;
	}
	else {
		this-> inverseMomentOfInertia = 0.0;
	}
	this->shape->UpdateVertices(rotation, position);
	
}

RigidBody::~RigidBody() {
	delete shape;
	SDL_DestroyTexture(texture);
}

void RigidBody::SetTexture(const char* filePath) {
	texture = IMG_LoadTexture(Graphics::renderer, filePath);
	// TODO check if texture is valid? This won't be even be here later though..
}

bool RigidBody::isStatic() const {
	const double epsilon = 0.005;
	return fabs(inverseMass - 0.0) < epsilon;
}
void RigidBody::AddForce(const Vector2& force) {
	sumOfForces += force;
}











