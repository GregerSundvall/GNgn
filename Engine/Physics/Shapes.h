#pragma once
#include <vector>

#include "../Misc.h"


enum ShapeType
{
	CIRCLE, POLYGON, BOX
};


class Shape {
public:
	virtual ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
	virtual void UpdateVertices(double angle,  const Vector2& position) = 0;
	virtual double GetMomentOfInertia() const = 0;
};

class Circle : public Shape {
public:
	float radius;

	Circle(const double radius);
	virtual ~Circle();
	ShapeType GetType() const override;
	Shape* Clone() const override;
	void UpdateVertices(double angle, const Vector2& position) override;
	double GetMomentOfInertia() const override;
};


class Polygon : public Shape {
public:
	double width;
	double height;

	std::vector<Vector2> localVertices;
	std::vector<Vector2> worldVertices;

	Polygon() = default;
	Polygon(const std::vector<Vector2> vertices);
	virtual ~Polygon();
	ShapeType GetType() const override;
	Shape* Clone() const override;
	Vector2 EdgeAt(int index) const;
	double FindMinSeparation(const Polygon* other, int& indexReferenceEdge, Vector2& supportPoint) const;
	int FindIncidentEdge(const Vector2& normal) const;
	int ClipSegmentToLine(const std::vector<Vector2>& contactsIn, std::vector<Vector2>& contactsOut,
		const Vector2& c0, const Vector2& c1) const;
	double PolygonArea() const;
	Vector2 PolygonCentroid() const;
	double GetMomentOfInertia() const override;
	void UpdateVertices(double angle, const Vector2& position) override;
};

class Box : public Polygon {
public:
	Box(double width, double height);
	virtual ~Box();
	ShapeType GetType() const override;
	Shape* Clone() const override;
	double GetMomentOfInertia() const override;
};