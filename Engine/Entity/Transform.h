#pragma once
#include "../Misc/Vector2.h"


class Transform
{
	Vector2 position;
	double rotation;
	Vector2 size;
public:
	Transform(Vector2 position = Vector2(0,0),
	                   double rotation = 0,
	                   Vector2 size = Vector2(32,32));

	void SetPosition(Vector2 position);
	Vector2 GetPosition() const;

	void SetRotation(double rotation);
	double GetRotation() const;
	
	void SetSize(Vector2 size);
	Vector2 GetSize() const;
};
