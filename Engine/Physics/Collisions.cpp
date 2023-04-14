#include "Collisions.h"



bool Collisions::IsColliding(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	bool aIsCircle = a->GetShapeType() == CIRCLE;
	bool bIsCircle = b->GetShapeType() == CIRCLE;
	bool aIsPolygon = a->GetShapeType() == POLYGON || a->GetShapeType() == POLYGON;
	bool bIsPolygon = b->GetShapeType() == POLYGON || b->GetShapeType() == POLYGON;

	if (aIsCircle && bIsCircle) { return CircleCircleCollision(a, b, contacts); }
	if (aIsPolygon && bIsPolygon) { return PolygonPolygonCollision(a, b, contacts); }
	if ( aIsPolygon && bIsCircle) { return PolygonCircleCollision(a, b, contacts); }
	if (aIsCircle && bIsPolygon) { return PolygonCircleCollision(b, a, contacts); }

	return false;
}

bool Collisions::CircleCircleCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	Shape* circleA = &a->shape;
	Shape* circleB = &b->shape;

	const Vector2 ab = b->position - a->position;
	const double sumOfRadii = circleA->GetRadius() + circleB->GetRadius();

	bool isColliding = ab.MagnitudeSquared() <= (sumOfRadii * sumOfRadii);
	if (!isColliding) return false;
	
	Contact contact;
	contact.a = a;
	contact.b = b;
	contact.normal = ab;
	contact.normal.Normalize();
	contact.start = b->position - contact.normal * circleB->GetRadius();
	contact.start = a->position + contact.normal * circleA->GetRadius();
	contact.depth = (contact.end - contact.start).Magnitude();
	contacts.push_back(contact);
	
	return true;
}

bool Collisions::PolygonPolygonCollision(RigidBody* a, RigidBody* b, std::vector<Contact>& contacts) {
	Shape* polygonA = &a->shape;
	Shape* polygonB = &b->shape;
	int ReferenceEdgeIndexA, ReferenceEdgeIndexB;
	Vector2 SupportPointA, SupportPointB;
	
	double separationAB = polygonA->FindMinSeparation(polygonB, ReferenceEdgeIndexA, SupportPointA);
	if (separationAB >= 0) return false;
	double separationBA = polygonB->FindMinSeparation(polygonA, ReferenceEdgeIndexB, SupportPointB);
	if (separationBA >= 0) return false;

	Shape* referenceShape;
	Shape* incidentShape;
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
	const std::vector<Vector2>* incidentShapeVertices = incidentShape->GetVertices();
	int incidentIndex = incidentShape->FindIncidentEdge(referenceEdge.Normal());
	int incidentNextIndex = (incidentIndex +1) % incidentShapeVertices->size();
	Vector2 vertex0 = incidentShapeVertices->at(incidentIndex);
	Vector2 vertex1 = incidentShapeVertices->at(incidentNextIndex);

	const std::vector<Vector2>* referenceShapeVertices = referenceShape->GetVertices();
	std::vector<Vector2> contactPoints = {vertex0, vertex1};
	std::vector<Vector2> clippedPoints = contactPoints;
	for (int i = 0; i < referenceShapeVertices->size(); ++i) {
		if (i == referenceEdgeIndex)
			continue;

		Vector2 clipped0 = referenceShapeVertices->at(i);
		Vector2 clipped1 = referenceShapeVertices->at((i + 1) % referenceShapeVertices->size());
		int clippedCount = referenceShape->ClipSegmentToLine(contactPoints, clippedPoints, clipped0, clipped1);
		if (clippedCount < 2)
			break;

		contactPoints = clippedPoints;
	}

	Vector2 referenceVertex = referenceShapeVertices->at(referenceEdgeIndex);
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

bool Collisions::PolygonCircleCollision(RigidBody* polygonRB, RigidBody* circleRB, std::vector<Contact>& contacts) {
	const Shape* polygon = &polygonRB->shape;
	const Shape* circle = &circleRB->shape;
	const std::vector<Vector2>* polygonVertices = polygonRB->shape.GetVertices();

	bool isOutside = false;
	Vector2 minCurrentVertex;
	Vector2 minNextVertex;
	double distanceCircleEdge = std::numeric_limits<double>::lowest();

	// Find the edge nearest to circle center
	for (int i = 0; i < polygonVertices->size(); ++i)
	{
		int currentVertex = i;
		int nextVertex = (i + 1) % polygonVertices->size();
		Vector2 edge = polygon->EdgeAt(currentVertex);
		Vector2 normal = edge.Normal();

		Vector2 vertexToCircleCenter = circleRB->position - polygonVertices->at(currentVertex); 
		double projection = vertexToCircleCenter.Dot(normal);

		if (projection > 0) {
			// Circle center is outside polygon
			distanceCircleEdge = projection;
			minCurrentVertex = polygonVertices->at(currentVertex);
			minNextVertex = polygonVertices->at(nextVertex);
			isOutside = true;
			break;
		}
		if (projection > distanceCircleEdge) {
			// Circle center is inside polygon. Continue checking to find least negative projection.
			// But is this really getting the "nearest" one?
			distanceCircleEdge = projection;
			minCurrentVertex = polygonVertices->at(currentVertex);
			minNextVertex = polygonVertices->at(nextVertex);
		}
	}

	// TODO Refactor below

	Contact contact;
	double circleRadius = circle->GetRadius();
	if (isOutside) {
        // Check if we are inside region A:
        Vector2 v1 = circleRB->position - minCurrentVertex; 
        Vector2 v2 = minNextVertex - minCurrentVertex; // the nearest edge (from curr vertex to next vertex)
        if (v1.Dot(v2) < 0) {
            // Distance from vertex to circle center is greater than radius... no collision
            if (v1.Magnitude() > circleRadius) {
                return false;
            } else {
                // Detected collision in region A:
                contact.a = polygonRB;
                contact.b = circleRB;
                contact.depth = circleRadius - v1.Magnitude();
                contact.normal = v1.Normalize();
                contact.start = circleRB->position + (contact.normal * -circleRadius);
                contact.end = contact.start + (contact.normal * contact.depth);
            }
        } else {
            // Check if we are inside region B:
            v1 = circleRB->position - minNextVertex; 
            v2 = minCurrentVertex - minNextVertex;   // the nearest edge
            if (v1.Dot(v2) < 0) {
	            if (v1.Magnitude() > circleRadius) {
		            // No collision
		            return false;
                } else {
                    // Detected collision in region B:
                    contact.a = polygonRB;
                    contact.b = circleRB;
                    contact.depth = circleRadius - v1.Magnitude();
                    contact.normal = v1.Normalize();
                    contact.start = circleRB->position + (contact.normal * -circleRadius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            } else {
                // We are inside region C:
                if (distanceCircleEdge > circleRadius) {
                    // No collision
                    return false;
                } else {
                    // Detected collision in region C:
                    contact.a = polygonRB;
                    contact.b = circleRB;
                    contact.depth = circleRadius - distanceCircleEdge;
                    contact.normal = (minNextVertex - minCurrentVertex).Normal();
                    contact.start = circleRB->position - (contact.normal * circleRadius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            }
        }
    } else {
        // The center of circle is inside the polygon... it is definitely colliding!
        contact.a = polygonRB;
        contact.b = circleRB;
        contact.depth = circleRadius - distanceCircleEdge;
        contact.normal = (minNextVertex - minCurrentVertex).Normal();
        contact.start = circleRB->position - (contact.normal * circleRadius);
        contact.end = contact.start + (contact.normal * contact.depth);
    }

    contacts.push_back(contact);

    return true;
	
	
}










































