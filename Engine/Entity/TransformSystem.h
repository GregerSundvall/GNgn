#pragma once
#include <vector>

#include "Transform.h"


static std::vector<Transform> transforms = {};

class TransformSystem
{
public:
	static Vector2& GetPosition(int transformID);
	// static Transform& GetTransform(const int transformID);
	
};
