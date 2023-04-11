#pragma once

#include <SDL_shape.h>
#include <vector>

#include "Transform.h"
#include "../Misc/Misc.h"
#include "../Misc/Vector2.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Shapes.h"



class Entity
{
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

	SDL_Texture* texture;
	
	ShapeType shapeType;
	Box box;
	Circle circle;
	Polygon polygon;
public:
	// Box entity
	Entity(double x, double y, double width, double height, double weight, const char* filePath);
	// Circle entity
	// Entity(double x, double y, double radius, double weight, const char* filePath);
	
	virtual void Update(double deltaTime);




	
	void SetPosition(Vector2 const position);
	void SetRotation(double rotation);
	void SetWidthHeight(double width, double height);
	void SetDiameter(double diameter);
	void SetMass(double weight);
	void SetShape(const Shape& shape);
	void SetTexture(const char* filePath);
	
	Vector2 GetPosition();
	double GetRotation();
	Vector2 GetWidthHeight();
	double GetDiameter();
	double GetMass();
	Shape* GetShape();

	bool isStatic() const;

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


