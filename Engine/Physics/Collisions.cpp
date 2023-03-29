#include "Collisions.h"



bool Collisions::IsColliding(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	bool aIsCircle = a->shape->GetType() == CIRCLE;
	bool bIsCircle = b->shape->GetType() == CIRCLE;
	bool aIsPolygon = a->shape->GetType() == POLYGON || a->shape->GetType() == BOX;
	bool bIsPolygon = b->shape->GetType() == POLYGON || b->shape->GetType() == BOX;

	if (aIsCircle && bIsCircle) { return CircleCircleCollision(a, b, contacts); }
	if (aIsPolygon && bIsPolygon) { return PolygonPolygonCollision(a, b, contacts); }
	if ( aIsPolygon && bIsCircle) { return PolygonCircleCollision(a, b, contacts); }
	if (aIsCircle && bIsPolygon) { return PolygonCircleCollision(b, a, contacts); }

	return false;
}

bool Collisions::CircleCircleCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	Circle* circleA = (Circle*)a->shape;
	Circle* circleB = (Circle*)b->shape;

	const Vector2 ab = b->position - a->position;
	const double sumOfRadii = circleA->radius + circleB->radius;

	bool isColliding = ab.MagnitudeSquared() <= (sumOfRadii * sumOfRadii);
	if (!isColliding) return false;
	
	Contact contact(a, b);
	contact.start = b->position - contact.normal * circleB->radius;
	contact.start = a->position + contact.normal * circleA->radius;
	contact.depth = (contact.end - contact.start).Magnitude();
	contacts.push_back(contact);
	
	return true;
}

bool Collisions::PolygonPolygonCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	Polygon* polygonA = (Polygon*)a->shape;
	Polygon* polygonB = (Polygon*)b->shape;
	int ReferenceEdgeIndexA, ReferenceEdgeIndexB;
	Vector2 SupportPointA, SupportPointB;
	
	double separationAB = polygonA->FindMinSeparation(polygonB, ReferenceEdgeIndexA, SupportPointA);
	if (separationAB >= 0) return false;
	double separationBA = polygonB->FindMinSeparation(polygonA, ReferenceEdgeIndexB, SupportPointB);
	if (separationBA >= 0) return false;

	Polygon* referenceShape;
	Polygon* incidentShape;
	int referenceEdgeIndex;
	if (separationAB > separationBA) {
		referenceShape = polygonA;
		incidentShape = polygonB;
		referenceEdgeIndex = ReferenceEdgeIndexA;
	}
	else{
		referenceShape = polygonB;
		incidentShape = polygonA;
		referenceEdgeIndex = ReferenceEdgeIndexB;
	}

	Vector2 referenceEdge = referenceShape->EdgeAt(referenceEdgeIndex);

	// Clipping, in case the penetrating(penetrated?) edge is not fully inside other shape.
	int incidentIndex = incidentShape->FindIncidentEdge(referenceEdge.Normal());
	int incidentNextIndex = (incidentIndex +1) % incidentShape->worldVertices.size();
	Vector2 vertex0 = incidentShape->worldVertices[incidentIndex];
	Vector2 vertex1 = incidentShape->worldVertices[incidentNextIndex];

	std::vector<Vector2> contactPoints = {vertex0, vertex1};
	std::vector<Vector2> clippedPoints = contactPoints;
	for (int i = 0; i < referenceShape->worldVertices.size(); ++i) {
		if (i == referenceEdgeIndex)
			continue;

		Vector2 clipped0 = referenceShape->worldVertices[i];
		Vector2 clipped1 = referenceShape->worldVertices[(i + 1) % referenceShape->worldVertices.size()];
		int clippedCount = referenceShape->ClipSegmentToLine(contactPoints, clippedPoints,
		                                                     clipped0, clipped1);
		if (clippedCount < 2)
			break;

		contactPoints = clippedPoints;
	}

	Vector2 referenceVertex = referenceShape->worldVertices[referenceEdgeIndex];
	for (auto clippedVertex : clippedPoints) {
		double separation = (clippedVertex - referenceVertex).Dot(referenceEdge.Normal());
		if (separation <= 0) {
			Contact contact = {a, b};
			contact.normal = referenceEdge.Normal();
			contact.start = clippedVertex;
			contact.end = clippedVertex + contact.normal * -separation;
			// Making sure start-end points and normal is from a to b.
			if (separationBA >= separationAB) {
				std::swap(contact.start, contact.end);
				contact.normal *= -1.0;
			}
			contacts.push_back(contact);
		}
	}
	return true;
}

bool Collisions::PolygonCircleCollision(RigidBody* polygon, RigidBody* circle, std::vector<Contact>& contacts) {
	
}










































