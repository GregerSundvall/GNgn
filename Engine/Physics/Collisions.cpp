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
	
	Contact contact;
	contact.a = a;
	contact.b = b;
	contact.normal = ab;
	contact.normal.Normalize();
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

bool Collisions::PolygonCircleCollision(RigidBody* polygonRB, RigidBody* circleRB, std::vector<Contact>& contacts) {
	const Polygon* polygon = (Polygon*)polygonRB->shape;
	const Circle* circle = (Circle*)circleRB->shape;
	const std::vector<Vector2>& polygonVertices = polygon->worldVertices;

	bool isOutside = false;
	Vector2 minCurrentVertex;
	Vector2 minNextVertex;
	double distanceCircleEdge = std::numeric_limits<double>::lowest();

	// Find the edge nearest to circle center
	for (int i = 0; i < polygonVertices.size(); ++i)
	{
		int currentVertex = i;
		int nextVertex = (i + 1) % polygonVertices.size();
		Vector2 edge = polygon->EdgeAt(currentVertex);
		Vector2 normal = edge.Normal();

		Vector2 vertexToCircleCenter = circleRB->position - polygonVertices[currentVertex]; 
		double projection = vertexToCircleCenter.Dot(normal);

		if (projection > 0) {
			// Circle center is outside polygon
			distanceCircleEdge = projection;
			minCurrentVertex = polygonVertices[currentVertex];
			minNextVertex = polygonVertices[nextVertex];
			isOutside = true;
			break;
		}
		if (projection > distanceCircleEdge) {
			// Circle center is inside polygon. Continue checking to find least negative projection.
			// But is this really getting the "nearest" one?
			distanceCircleEdge = projection;
			minCurrentVertex = polygonVertices[currentVertex];
			minNextVertex = polygonVertices[nextVertex];
		}
	}

	// TODO Refactor below

	Contact contact;
	if (isOutside) {
        // Check if we are inside region A:
        Vector2 v1 = circleRB->position - minCurrentVertex; 
        Vector2 v2 = minNextVertex - minCurrentVertex; // the nearest edge (from curr vertex to next vertex)
        if (v1.Dot(v2) < 0) {
            // Distance from vertex to circle center is greater than radius... no collision
            if (v1.Magnitude() > circle->radius) {
                return false;
            } else {
                // Detected collision in region A:
                contact.a = polygonRB;
                contact.b = circleRB;
                contact.depth = circle->radius - v1.Magnitude();
                contact.normal = v1.Normalize();
                contact.start = circleRB->position + (contact.normal * -circle->radius);
                contact.end = contact.start + (contact.normal * contact.depth);
            }
        } else {
            // Check if we are inside region B:
            v1 = circleRB->position - minNextVertex; 
            v2 = minCurrentVertex - minNextVertex;   // the nearest edge
            if (v1.Dot(v2) < 0) {
	            if (v1.Magnitude() > circle->radius) {
		            // No collision
		            return false;
                } else {
                    // Detected collision in region B:
                    contact.a = polygonRB;
                    contact.b = circleRB;
                    contact.depth = circle->radius - v1.Magnitude();
                    contact.normal = v1.Normalize();
                    contact.start = circleRB->position + (contact.normal * -circle->radius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            } else {
                // We are inside region C:
                if (distanceCircleEdge > circle->radius) {
                    // No collision
                    return false;
                } else {
                    // Detected collision in region C:
                    contact.a = polygonRB;
                    contact.b = circleRB;
                    contact.depth = circle->radius - distanceCircleEdge;
                    contact.normal = (minNextVertex - minCurrentVertex).Normal();
                    contact.start = circleRB->position - (contact.normal * circle->radius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            }
        }
    } else {
        // The center of circle is inside the polygon... it is definitely colliding!
        contact.a = polygonRB;
        contact.b = circleRB;
        contact.depth = circle->radius - distanceCircleEdge;
        contact.normal = (minNextVertex - minCurrentVertex).Normal();
        contact.start = circleRB->position - (contact.normal * circle->radius);
        contact.end = contact.start + (contact.normal * contact.depth);
    }

    contacts.push_back(contact);

    return true;
	
	
}










































