#pragma once
#include <SDL_render.h>

#include "Shapes.h"
#include "../Misc.h"

class RigidBody
{
public:
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

	Shape* shape = nullptr;
	SDL_Texture* texture = nullptr;

	RigidBody(const Shape& shape, double x, double y, double mass);
	~RigidBody();

	bool isStatic() const;

	void AddForce(const Vector2& force);
	void AddTorque(double torque);
	void ClearForces();
	void ClearTorque();
	
	void SetTexture(const char* filePath);

	Vector2 LocalToWorldSpace(const Vector2& point) const;
	Vector2 WorldToLocalSpace(const Vector2& point) const;

	void ApplyImpulseLinear(const Vector2& j);
	void ApplyImpulseAngular(const double j);
	void ApplyImpulseAtPoint(const Vector2& j, const Vector2& r);

	void integrateLinear(double deltaTime);
	void integrateVelocities(const double deltaTime);
};
