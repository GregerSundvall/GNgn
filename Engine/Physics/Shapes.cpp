#include "Shapes.h"

#include <complex>


Circle::Circle(const double radius) {
	this->radius = radius;
}

Circle::~Circle() {}

Shape* Circle::Clone() const {
	return new Circle(radius);
}

void Circle::UpdateVertices(double angle, const Vector2& position) {
	return; // It's a circle, no vertices.
}

ShapeType Circle::GetType() const {
	return CIRCLE;
}

double Circle::GetMomentOfInertia() const {
	return 0.5 * radius * radius;
}

Polygon::Polygon(const std::vector<Vector2> vertices) {
	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::lowest();
	double maxY = std::numeric_limits<double>::lowest();

	for (auto vertex : vertices) {
		localVertices.push_back(vertex);
		worldVertices.push_back(vertex);

		minX = std::min(minX, vertex.x);
		maxX = std::min(maxX, vertex.x);
		minY = std::min(minY, vertex.y);
		maxY = std::min(maxY, vertex.y);
	}
	width = maxX - minX;
	height = maxY - minY;
}

Polygon::~Polygon() {}

ShapeType Polygon::GetType() const {
	return POLYGON;
}

Shape* Polygon::Clone() const {
	return new Polygon(localVertices);
}

double Polygon::PolygonArea() const {
	double area = 0;
	for (int i = 0; i < localVertices.size(); ++i) {
		int j = (i = 1) % localVertices.size();
		area += localVertices[i].Cross(localVertices[j]);
	}
	return area / 2;
}

Vector2 Polygon::PolygonCentroid() const {
	Vector2 sum = {0, 0};
	for (int i = 0; i < localVertices.size(); ++i) {
		int j = (i+1) % localVertices.size();
		sum += (localVertices[i] + localVertices[j]) * localVertices[i].Cross(localVertices[j]);
	}
	return sum / 6 / PolygonArea(); // TODO was this supposed to be specifically 6?
}

double Polygon::GetMomentOfInertia() const {
	double acc0 = 0;
	double acc1 = 0;
	for (int i = 0; i < localVertices.size(); ++i) {
		Vector2 a = localVertices[i];
		Vector2 b = localVertices[(i + 1) % localVertices.size()];
		double cross = abs(a.Cross(b));
		acc0 += cross * (a.Dot(a) + b.Dot(b) + a.Dot(b));
		acc1 += cross;
	}
	return acc0 / 6 / acc1; // TODO was this supposed to be specifically 6?
}

Vector2 Polygon::EdgeAt(int index) const {
	int currentVertex = index;
	int nextVertex = (index + 1) % worldVertices.size();
	return worldVertices[nextVertex] - worldVertices[currentVertex];
}

double Polygon::FindMinSeparation(const Polygon* other, int& indexReferenceEdge, Vector2& supportPoint) const {
	double separation = std::numeric_limits<double>::lowest();
	
	for (int i = 0; i < this->worldVertices.size(); ++i) {
		Vector2 vectorA = this->worldVertices[i];
		Vector2 normal = this->EdgeAt(i).Normal();
		double minSeparation = std::numeric_limits<double>::max();
		Vector2 minVertex;
		for (int j = 0; j < other->worldVertices.size(); ++j) {
			Vector2 vectorB = other->worldVertices[j];
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

int Polygon::FindIncidentEdge(const Vector2& normal) const {
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

int Polygon::ClipSegmentToLine(const std::vector<Vector2>& contactsIn, std::vector<Vector2>& contactsOut, const Vector2& c0, const Vector2& c1) const {
	int numOut = 0;
	// Distances of end points to the line
	Vector2 normal = (c1 - c0).Normalize();
	double distance0 = (contactsIn[0] - c0).Cross(normal);
	double distance1 = (contactsIn[1] - c0).Cross(normal);
	// If points are "behind" the plane, set contactsOut to in-value:
	if ( distance0 <= 0) { contactsOut[numOut++] = contactsIn[0]; }
	if ( distance1 <= 0) { contactsOut[numOut++] = contactsIn[1]; }
	// If points are on different sides of the plane, set contactsOut to clipped point:
	if (distance0 * distance1 < 0) {
		double totalDistance = distance0 - distance1;
		// Find intersection
		double t = distance0 / totalDistance;
		Vector2 cp = contactsIn[0] + (contactsIn[1] - contactsIn[0]) * t;
		contactsOut[numOut] = cp;
		numOut++;
	}
	return numOut;
}

void Polygon::UpdateVertices(double angle, const Vector2& position) {
	// Update world space values, from computed local space values
	for (int i = 0; i < localVertices.size(); ++i){
		worldVertices[i] = localVertices[i].Rotated(angle);
		worldVertices[i] += position;
	}
}

Box::Box(double width, double height) {
	this->width = width;
	this->height = height;
    
	localVertices.push_back(Vector2(-width / 2.0, -height / 2.0));
	localVertices.push_back(Vector2(+width / 2.0, -height / 2.0));
	localVertices.push_back(Vector2(+width / 2.0, +height / 2.0));
	localVertices.push_back(Vector2(-width / 2.0, +height / 2.0));

	worldVertices.push_back(Vector2(-width / 2.0, -height / 2.0));
	worldVertices.push_back(Vector2(+width / 2.0, -height / 2.0));
	worldVertices.push_back(Vector2(+width / 2.0, +height / 2.0));
	worldVertices.push_back(Vector2(-width / 2.0, +height / 2.0));
}

Box::~Box() {}
ShapeType Box::GetType() const { return BOX; }
Shape* Box::Clone() const { return new Box(width, height); }

double Box::GetMomentOfInertia() const {
	// TODO should also be multiplied by the RB's mass I guess?
	return 0.083333 * (width * width + height * height);
}










