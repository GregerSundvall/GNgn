#include "TransformSystem.h"

#include <algorithm>


void TransformSystem::Init() {
	transforms.reserve(1000);
}

int TransformSystem::Create(Vector2 const& position, double const rotation, Vector2 const& size) {
	transforms.emplace_back(Transform(position, rotation, size));
	return transforms.size() -1;
}

void TransformSystem::SetPosition(int const transformID, Vector2 const position) {
	transforms.at(transformID).SetPosition(position);
}

Vector2 TransformSystem::GetPosition(int const transformID) {
	return transforms.at(transformID).GetPosition();
}

void TransformSystem::SetRotation(int const transformID, double const rotation) {
	transforms.at(transformID).SetRotation(rotation);
}
double TransformSystem::GetRotation(int const transformID) {
	return transforms.at(transformID).GetRotation();
}

void TransformSystem::SetSize(int const transformID, Vector2 const size) {
	transforms.at(transformID).SetSize(size);
}
Vector2 TransformSystem::GetSize(int const transformID) {
	return transforms.at(transformID).GetSize();
}

// Transform& TransformSystem::GetTransform(const int transformID) {
// 	return transforms.at(transformID);
// }
