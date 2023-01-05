#include "Player.h"

#include "Game.h"
#include "../Engine/Components.h"

Player::Player(std::string name, float size, Game* game)
{
    this->name = name;
    this->game = game;
    entityID = entitySystem->CreateEntity();
    entitySystem->AddTransform(entityID,
        Float2(400 - size/2.f, 900), Float2(size, size));
    entitySystem->AddCollider(entityID);
    entitySystem->AddSprite(entityID, "Res/Ships/player.png");
    entitySystem->AddMovement(entityID, Float2(0, 0));
}

void Player::Update()
{
    if (!isAlive) { return; }
    
    Float2 velocity = Float2(input->A * -1.0f + input->D * 1.0f, 0);
    SetVelocity(velocity);

    if (input->Space == 1)
    {
        Shoot();
    }
}

void Player::Shoot()
{
    Float2 position = *entitySystem->GetPosition(entityID);
    Float2 offsetY = Float2(0, -2); 
    position += offsetY; //To spawn just ahead of ship
    
    float playersize = entitySystem->GetTransform(entityID)->size.x;
    float bulletSize = 8;
    Float2 centeringOffset = Float2(playersize/2 - bulletSize/2, 0);
    position += centeringOffset; // center x pos of ship
    
    Float2 velocity = Float2(0, -10.0f);
    game->SpawnBullet(position, velocity, bulletSize);
}

void Player::WasKilled()
{ isAlive = false; entityID = -1; }

Float2* Player::GetPosition()
{ return entitySystem->GetPosition(EID()); }

void Player::SetVelocity(Float2 velocity)
{ entitySystem->SetVelocity(entityID, velocity); }
