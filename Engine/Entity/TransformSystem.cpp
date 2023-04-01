#include "TransformSystem.h"



Vector2& TransformSystem::GetPosition(int const transformID) {
	return transforms.at(transformID).GetPosition();
}

// Transform& TransformSystem::GetTransform(const int transformID) {
// 	return transforms.at(transformID);
// }
