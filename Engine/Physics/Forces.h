#pragma once
#include "RigidBody.h"


class Forces
{
public:
	static Vector2 GenerateDragForce(const RigidBody& rigidBody, float k);
	static Vector2 GenerateFrictionForce(const RigidBody& rigidBody, float k);
	static Vector2 GenerateSpringForce(const RigidBody& rigidBody, Vector2 anchor, float restLength, float k);
	static Vector2 GenerateGravitationalForce(const RigidBody& a, const RigidBody& b, float G, float minDistance, float maxDistance);
};
