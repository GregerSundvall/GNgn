#include "Player.h"
#include "../Engine/Components.h"

Player::Player(std::string name, float size)
{
    this->name = name;
    entityID = entitySystem->CreateEntity();
    entitySystem->AddTransform(entityID,
        Float2(400 - size/2.f, 900), Float2(size, size));
    entitySystem->AddCollider(entityID);
    entitySystem->AddSprite(entityID, Color(100, 100, 100));
    entitySystem->AddMovement(entityID, Float2(0, 0));
}

void Player::WasKilled()
{ isAlive = false; entityID = -1; }

Float2* Player::GetPosition()
{ return entitySystem->GetPosition(EID()); }

void Player::SetVelocity(Float2 velocity)
{ entitySystem->SetVelocity(entityID, velocity); }
