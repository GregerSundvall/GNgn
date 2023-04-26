#pragma once
#include "RigidBody.h"
#include "../Misc/Vector2.h"

struct Contact
{
	RigidBody* a;
	RigidBody* b;

	Vector2 start;
	Vector2 end;

	Vector2 normal;
	double depth;
};


class Collisions
{
public:
	static bool IsColliding(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts);
	static bool CircleCircleCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts);
	static bool PolygonPolygonCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts);
	static bool PolygonCircleCollision(RigidBody* polygonRB, RigidBody* circleRB, std::vector<Contact>& contacts);
};
