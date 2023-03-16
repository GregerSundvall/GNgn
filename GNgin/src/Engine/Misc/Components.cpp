﻿#include "Components.h"
#include "../Entities/EntitySystem.h"


void Entity::AddTransform(Float2 position, Float2 size)
{
    entitySystem->AddTransform(eID, position, size);
}

void Entity::AddMovement(Float2 velocity)
{
    entitySystem->AddMovement(eID, velocity);
}

void Entity::AddCollision()
{
    entitySystem->AddCollider(eID);
}

void Entity::AddSprite(Color color)
{
    entitySystem->AddSprite(eID, color);
}

void Entity::AddSprite(int textureID)
{
    entitySystem->AddSprite(eID, textureID);
}

void Entity::AddSprite(std::string text, std::string fontPath)
{
    entitySystem->AddSprite(eID, text, fontPath);
}
