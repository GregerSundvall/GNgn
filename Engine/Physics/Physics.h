#pragma once
#include <vector>

#include "Shapes.h"
#include "../Misc/Vector2.h"
#include "RigidBody.h"

class Box;
// class RigidBody;
class Constraint;

// static std::vector<Shape>* rigidBodiesStatic;

class Physics
{
	double gravity = 9.8;
	int iterationCount = 10;
	int pixelsPerMeter = 50;

	static std::vector<RigidBody> rigidBodies;
	
	std::vector<Constraint*> constraints;

	std::vector<Vector2> forces;
	std::vector<double> torques;

public:
	Physics(double gravity);
	~Physics();

	// Create box rb
	static RigidBody* Create(double x, double y, double width, double height, double mass);

	static std::vector<RigidBody>* GetRigidBodies();
	// Create circle rb
	// static Circle* Create(double radius);
	// void AddBody(RigidBody* body);

	// static Vector2* GetPosition(int rigidBodyID);
	// static double GetRotation(int rigidBodyID);

	// static std::vector<RigidBody>* GetRigidBodies();
	// static std::vector<RigidBody>* GetRigidBodiesStatic();

	void AddConstraint(Constraint* constraint);
	std::vector<Constraint*>& GetConstraints();

	void AddForce(const Vector2& force);
	void AddTorque(double torque);

	void Update(double deltaTime);


};
