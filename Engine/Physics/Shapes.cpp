#include "Shapes.h"


Shape::Shape() { type = UNINIT; }

Shape::Shape(const double radius) {
	type = CIRCLE;
	this->radius = radius;
}
Shape::Shape(const double width, const double height) {
	CreatePolygonFromVertices(std::vector<Vector2>{ {-width / 2, -height / 2}, {+width / 2, -height / 2}, {+width / 2, +height / 2}, {-width / 2, +height / 2}});
}
Shape::Shape(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d) {
	CreatePolygonFromVertices(std::vector{a, b, c, d});
}
Shape::Shape(const std::vector<Vector2> vertices) {
	CreatePolygonFromVertices(vertices);
}
Shape::~Shape() {}


void Shape::CreatePolygonFromVertices(const std::vector<Vector2> vertices) {
	type = POLYGON;
	
	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::lowest();
	double maxY = std::numeric_limits<double>::lowest();

	for (int i = 0; i < vertices.size(); ++i) {
		localVertices.emplace_back(vertices.at(i));
		worldVertices.emplace_back(vertices.at(i));

		minX = std::min(minX, vertices[i].x);
		maxX = std::min(maxX, vertices[i].x);
		minY = std::min(minY, vertices[i].y);
		maxY = std::min(maxY, vertices[i].y);
	}
	width = maxX - minX;
	height = maxY -minY;
}

Shape* Shape::Clone() const {
	if (type == CIRCLE) { return new Shape(radius); }
	return new Shape(localVertices);
}

void Shape::UpdateVertices(const double angle, const Vector2& position) {
	// Update world space values, from computed local space values
	for (int i = 0; i < localVertices.size(); ++i){
		worldVertices.at(i) = localVertices.at(i).Rotated(angle);
		worldVertices.at(i) += position;
	}
}


double Shape::GetMomentOfInertia() const {
	if (type == CIRCLE) {
		return radius * radius * 0.5; }
	// if (type == RECTANGLE) {
	// 	return 0.083333 * (width * width + height * height);
	// 	// 	Should also be multiplied by the RB's mass I guess?
	// }
	double acc0 = 0;
	double acc1 = 0;
	for (int i = 0; i < localVertices.size(); ++i) {
		Vector2 a = localVertices.at(i);
		Vector2 b = localVertices.at((i + 1) % localVertices.size());
		double cross = abs(a.Cross(b));
		acc0 += cross * (a.Dot(a) + b.Dot(b) + a.Dot(b));
		acc1 += cross;
	}
	return acc0 / 6 / acc1; 
}

Vector2 Shape::EdgeAt(const int index) const {
	int currentVertex = index;
	int nextVertex = (index + 1) % worldVertices.size();
	return worldVertices.at(nextVertex) - worldVertices.at(currentVertex);
}
double Shape::FindMinSeparation(const Shape* other, int& indexReferenceEdge, Vector2& supportPoint) const {
	double separation = std::numeric_limits<double>::lowest();
	
	for (int i = 0; i < this->worldVertices.size(); ++i) {
		Vector2 vectorA = this->worldVertices.at(i);
		Vector2 normal = this->EdgeAt(i).Normal();
		double minSeparation = std::numeric_limits<double>::max();
		Vector2 minVertex;
		for (int j = 0; j < other->worldVertices.size(); ++j) {
			Vector2 vectorB = other->worldVertices.at(j);
			double projection = (vectorA - vectorB).Dot(normal);
			if (projection < minSeparation) {
				minSeparation = projection;
				minVertex = vectorB;
			}
		}
		if (minSeparation > separation) {
			separation = minSeparation;
			indexReferenceEdge = i;
			supportPoint = minVertex;
		}
	}
	return separation;
}
int Shape::FindIncidentEdge(const Vector2& normal) const {
	int indexIncidentEdge;
	double minProjection = std::numeric_limits<double>::max();
	for (int i = 0; i < this->worldVertices.size(); ++i){
		Vector2 edgeNormal = this->EdgeAt(i).Normal();
		double projection = edgeNormal.Dot(normal);
		if (projection < minProjection) {
			minProjection = projection;
			indexIncidentEdge = i;
		}
	}
	return indexIncidentEdge;
}
int Shape::ClipSegmentToLine(const std::vector<Vector2>& contactsIn, std::vector<Vector2>& contactsOut, const Vector2& c0, const Vector2& c1) const {
	int numOut = 0;
	// Distances of end points to the line
	Vector2 normal = (c1 - c0).Normalize();
	double distance0 = (contactsIn.at(0) - c0).Cross(normal);
	double distance1 = (contactsIn.at(1) - c0).Cross(normal);
	// If points are "behind" the plane, set contactsOut to in-value:
	if ( distance0 <= 0) { contactsOut.at(numOut++) = contactsIn.at(0); }
	if ( distance1 <= 0) { contactsOut.at(numOut++) = contactsIn.at(1); }
	// If points are on different sides of the plane, set contactsOut to clipped point:
	if (distance0 * distance1 < 0) {
		double totalDistance = distance0 - distance1;
		// Find intersection
		double t = distance0 / totalDistance;
		Vector2 cp = contactsIn.at(0) + (contactsIn.at(1) - contactsIn.at(0)) * t;
		contactsOut.at(numOut) = cp;
		numOut++;
	}
	return numOut;
}

double Shape::PolygonArea() const {
	double area = 0;
	for (int i = 0; i < localVertices.size(); ++i) {
		int j = (i = 1) % localVertices.size();
		area += localVertices.at(i).Cross(localVertices.at(j));
	}
	return area / 2;
}

Vector2 Shape::PolygonCentroid() const {
	Vector2 sum = {0, 0};
	for (int i = 0; i < localVertices.size(); ++i) {
		int j = (i+1) % localVertices.size();
		sum += (localVertices.at(i) + localVertices.at(j)) * localVertices.at(i).Cross(localVertices.at(j));
	}
	return sum / 6 / PolygonArea();
}

Vector2 Shape::GetBoxSize() const { return {width, height}; }
ShapeType Shape::GetType() const { return type; }
double Shape::GetWidth() const { return width; }
double Shape::GetHeight() const { return height; }
double Shape::GetRadius() const { return radius; }
std::vector<Vector2>* Shape::GetVertices() { return &worldVertices; }

void Shape::SetRadius(double radius) {}


