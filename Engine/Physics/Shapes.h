#pragma once
#include "../Misc.h"


enum ShapeType
{
	CIRCLE, POLYGON, BOX
};


class Shape
{
public:
	virtual ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
	virtual void UpdateVertices(float angle,  const Vector2& position) = 0;
	virtual float GetMomentOfInertia() const = 0;
};

