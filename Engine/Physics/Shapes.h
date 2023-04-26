#pragma once
#include <vector>

#include "../Misc/Vector2.h"



enum ShapeType
{
	CIRCLE, POLYGON, BOX, UNINIT
};


class Shape {
	ShapeType type;
	double radius = 0;
	double width = 0;
	double height = 0;
	std::vector<Vector2> localVertices;
	std::vector<Vector2> worldVertices;
public:
	Shape();
	Shape(double radius);
	Shape(double width, double height);
	Shape(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
	Shape(std::vector<Vector2> vertices);
	~Shape();
	
	Shape* Clone() const;
	void UpdateVertices(double angle,  const Vector2& position);
private :
	void CreatePolygonFromVertices(std::vector<Vector2> vertices);
	
public:		
	double GetMomentOfInertia() const;
	Vector2 EdgeAt(int index) const;
	double FindMinSeparation(const Shape* other, int& indexReferenceEdge, Vector2& supportPoint) const;
	int FindIncidentEdge(const Vector2& normal) const;
	int ClipSegmentToLine(const std::vector<Vector2>& contactsIn, std::vector<Vector2>& contactsOut, const Vector2& c0, const Vector2& c1) const;
	double PolygonArea() const;
	Vector2 PolygonCentroid() const;
	
	ShapeType GetType() const;
	double GetWidth() const;
	double GetHeight() const;
	Vector2 GetBoxSize() const;
	double GetRadius() const;
	std::vector<Vector2>* GetVertices();

	void SetRadius(double radius);
	
};
