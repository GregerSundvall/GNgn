#pragma once

#include <vector>
#include "../Entities/RigidBody.h"


class Physics
{
private:
	float gravity = 9.8f;

	std::vector<RigidBody*> rigidBodies;
	std::vector<Vector2> forces;
	std::vector<float> torques;

public:
	Physics();
	~Physics();

	int AddRigidBody();
	void AddForce(const Vector2& force);
	void AddTorque(float torque);

	void Update(float dt);

	
};

