#pragma once
#include "Vector2.h"


class Sprite
{
public:
	int textureID;
	Vector2 position;
	Vector2 size;
	Sprite(int const textureID, Vector2 const position, Vector2 const size) {
		this->textureID = textureID;
		this->position = position;
		this->size = size;
	}
};
