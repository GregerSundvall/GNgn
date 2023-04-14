#pragma once
#include <SDL_render.h>

#include "Vector2.h"


class Sprite
{
public:
	SDL_Texture* texture;
	SDL_Rect rect;
	Vector2 position;
	Vector2 size;
	Sprite(SDL_Texture* texture, double x, double y, double width, double height) {
		this->texture = texture;
		rect = SDL_Rect(x, y, width, height);
	}
};



class VertexContainer
{
	int size_ = 0;
	Vector2 vertices[4] = {Vector2(), Vector2(), Vector2(), Vector2()};
public:
	VertexContainer() {}
	VertexContainer(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d) { 
		vertices[0] = a; vertices[1] = b; vertices[2] = c; vertices[3] = d;}
	Vector2 at(int const index) const {return vertices[index]; }
	Vector2* at(int const index) {return &vertices[index]; }
	void push_back(Vector2 const vector) { vertices[size_] = vector; }
	int size() const { return size_; }

	Vector2 operator [] (const int index) const { return vertices[index]; } 
	Vector2& operator [] (const int index) { return vertices[index]; }  
};