#pragma once
#include "../Misc.h"

class RigidBody
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
	float momentOfInertia;
	float inverseMomentOfInertia;

	float restitution;
	float friction;
	
	
public:
	
};
