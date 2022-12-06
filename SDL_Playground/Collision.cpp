#include "Collision.h"

void Collision::FreeCollider(int index)
{
    Colliders.at(index) = Collider();
    MemberCount--;
}
