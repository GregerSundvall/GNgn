#pragma once
#include <vector>

#include "Transform.h"


static std::vector<Transform> transforms;

class TransformSystem
{
public:
	static void Init();

	static int Create(
		Vector2 const& position = {0, 0},
		double rotation = 0,
		Vector2 const& size = {0, 0});
	
	static void SetPosition(int transformID, Vector2 position);
	static Vector2 GetPosition(int transformID);

	static void SetRotation(int transformID, double rotation);
	static double GetRotation(int transformID);
	
	static void SetSize(int transformID, Vector2 size);
	static Vector2 GetSize(int transformID);
	
};
