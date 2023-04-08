#pragma once
#include <vector>

#include "../Misc/Vector2.h"

class RigidBody;
class Constraint;



static std::vector<RigidBody>* rigidBodiesStatic;

class Physics
{
	double gravity = 9.8;
	int iterationCount = 10;
	int pixelsPerMeter;
	std::vector<RigidBody>* rigidBodies;
	std::vector<Constraint*> constraints;

	std::vector<Vector2> forces;
	std::vector<double> torques;

public:
	Physics(double gravity);
	~Physics();

	static int Create();
	// void AddBody(RigidBody* body);

	static Vector2* GetPosition(int rigidBodyID);
	static double GetRotation(int rigidBodyID);

	std::vector<RigidBody>& GetRigidBodies() const;
	static std::vector<RigidBody>* GetRigidBodiesStatic();

	void AddConstraint(Constraint* constraint);
	std::vector<Constraint*>& GetConstraints();

	void AddForce(const Vector2& force);
	void AddTorque(double torque);


	void Update(double deltaTime);


};
