#include "RigidBody.h"


#include "../Graphics/Graphics.h"


RigidBody::RigidBody(const double x, const double y, const double width, const double height, const double mass) {
	this->position = {x, y};
	this->shape = Shape(width, height);
	this->velocity = Vector2(0, 0);
	this->acceleration = Vector2(0,0);
	this->rotation = 0.0;
	this->angularVelocity = 0.0;
	this->angularAcceleration = 0.0;
	this->sumOfForces = Vector2(0, 0);
	this->sumOfAllTorque = 0.0;
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
	this->shape.UpdateVertices(rotation, position);
	
}

RigidBody::~RigidBody() {}


bool RigidBody::isStatic() const {
	const double epsilon = 0.005;
	return fabs(inverseMass - 0.0) < epsilon;
}

ShapeType RigidBody::GetShapeType() { return shape.GetType(); }

void RigidBody::AddForce(const Vector2& force) {
	sumOfForces += force;
}

void RigidBody::AddTorque(double torque) {
	sumOfAllTorque += torque;
}

void RigidBody::ClearForces() {
	sumOfForces = Vector2(0,0);
}

void RigidBody::ClearTorque() {
	sumOfAllTorque = 0;
}

Vector2 RigidBody::LocalToWorldSpace(const Vector2& point) const {
	Vector2 rotated = point.Rotated(rotation);
	return rotated + position;
}

Vector2 RigidBody::WorldToLocalSpace(const Vector2& point) const {
	double translatedX = point.x - position.x;
	double translatedY = point.y - position.y;
	double rotatedX = cos(-rotation) * translatedX - sin(-rotation) * translatedY;
	double rotatedY = cos(-rotation) * translatedY + sin(-rotation) * translatedX;
	return Vector2(rotatedX, rotatedY);
}

void RigidBody::ApplyLinearImpulse(const Vector2& j) {
	if (isStatic()) return;
	velocity += j * inverseMass;
}

void RigidBody::ApplyAngularImpulse(const double j) {
	if (isStatic())	return;
	angularVelocity += j * inverseMomentOfInertia;
}

void RigidBody::ApplyImpulseAtPoint(const Vector2& j, const Vector2& r) {
	if (isStatic()) return;
	velocity += j * inverseMass;
	angularVelocity += r.Cross(j) * inverseMomentOfInertia;
}

void RigidBody::IntegrateForces(const double deltaTime) {
	if (isStatic()) return;
	acceleration = sumOfForces * inverseMass;
	velocity += acceleration * deltaTime;
	angularAcceleration = sumOfAllTorque * inverseMomentOfInertia;
	angularVelocity += angularAcceleration * deltaTime;
	ClearForces();
	ClearTorque();
}

void RigidBody::IntegrateVelocities(const double deltaTime) {
	if (isStatic()) return;
	position += velocity * deltaTime;
	rotation += angularVelocity * deltaTime;
	shape.UpdateVertices(rotation, position);
}










