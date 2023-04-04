#pragma once
#include <vector>

#include "../Misc/Vector2.h"

class RigidBody;
class Constraint;


class Physics
{
	float gravity = 9.8;
	int iterationCount = 10;
	int pixelsPerMeter;
	std::vector<RigidBody*> rigidBodies;
	std::vector<Constraint*> constraints;

	std::vector<Vector2> forces;
	std::vector<double> torques;

public:
	Physics(double gravity);
	~Physics();

	RigidBody* Create();
	void AddBody(RigidBody* body);
	std::vector<RigidBody*>& GetBodies();

	void AddConstraint(Constraint* constraint);
	std::vector<Constraint*>& GetConstraints();

	void AddForce(const Vector2& force);
	void AddTorque(double torque);

	void Update(double deltaTime);


};
