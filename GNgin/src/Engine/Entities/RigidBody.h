#pragma once
#include "../Misc/Vector2.h"
#include "../Misc/Shapes.h"

struct RigidBody
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	float rotation;
	float angularVelocity;
	float angularAcceleration;

	Vector2 sumOfForces;
	float sumOfTorques;

	float mass;
	float inverseMass;
	float momOfInertia;
	float inverseMomOfInertia;

	float restitution;
	float friction;

	Shape* shape = nullptr;

	RigidBody(const Shape& shape, float x, float y, float mass);
	~RigidBody();
};

