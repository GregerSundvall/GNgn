#pragma once
#include "../Misc/Vector2.h"


class Transform
{
	Vector2 position;
	double rotation;
	Vector2 scale;
public:
	Transform(Vector2 position = Vector2(0,0),
		double rotation = 0,
		Vector2 scale = Vector2(1,1));
	Vector2& GetPosition();
	
};
