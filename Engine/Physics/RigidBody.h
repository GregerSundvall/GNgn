#pragma once

#include "Shapes.h"
#include "../Misc/Vector2.h"



class RigidBody
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	double rotation;
	double angularVelocity;
	double angularAcceleration;

	Vector2 sumOfForces;
	double sumOfAllTorque;

	double mass;
	double inverseMass;
	double momentOfInertia;
	double inverseMomentOfInertia;

	double restitution;
	double friction;

	Shape shape;

	RigidBody(double x, double y, double width, double height, double mass);
	~RigidBody();

	bool isStatic() const;
	ShapeType GetShapeType();

	void AddForce(const Vector2& force);
	void AddTorque(double torque);
	void ClearForces();
	void ClearTorque();
	
	Vector2 LocalToWorldSpace(const Vector2& point) const;
	Vector2 WorldToLocalSpace(const Vector2& point) const;

	void ApplyLinearImpulse(const Vector2& j);
	void ApplyAngularImpulse(const double j);
	void ApplyImpulseAtPoint(const Vector2& j, const Vector2& r);

	void IntegrateForces(const double deltaTime);
	void IntegrateVelocities(const double deltaTime);
};
