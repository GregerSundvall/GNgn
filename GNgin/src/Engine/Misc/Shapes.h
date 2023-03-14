#pragma once
#include "Vector2.h"
#include <vector>


enum ShapeType { CIRCLE, POLYGON, BOX };

struct Shape
{
	virtual ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
};

struct Circle : public Shape
{
	float radius;
};

struct Polygon : public Shape
{
	float radius;
};

struct Box : public Polygon
{
	float radius;
};
