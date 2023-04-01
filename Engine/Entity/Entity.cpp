#include "Entity.h"

#include "EntitySystem.h"
#include "TransformSystem.h"


Vector2& Entity::GetPosition() {
	return TransformSystem::GetPosition(transformID);
}
