#include "Forces.h"
#include <algorithm>

Vector2 Forces::GenerateDragForce(const RigidBody& rigidRigidBody, float k) {
    Vector2 dragForce = Vector2(0, 0);
    if (rigidRigidBody.velocity.MagnitudeSquared() > 0) {
        // Calculate the drag direction (inverse of velocity unit vector)
        Vector2 dragDirection = rigidRigidBody.velocity.UnitVector() * -1.0;

        // Calculate the drag magnitude, k * |v|^2
        float dragMagnitude = k * rigidRigidBody.velocity.MagnitudeSquared();

        // Generate the final drag force with direction and magnitude
        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vector2 Forces::GenerateFrictionForce(const RigidBody& rigidRigidBody, float k) {
    // Calculate the friction direction (inverse of velocity unit vector)
    Vector2 frictionDirection = rigidRigidBody.velocity.UnitVector() * -1.0;

    // Calculate the friction magnitude (just k, for now)
    float frictionMagnitude = k;

    // Calculate the final resulting friction force vector
    Vector2 frictionForce = frictionDirection * frictionMagnitude;
    return frictionForce;
}

Vector2 Forces::GenerateGravitationalForce(const RigidBody& a, const RigidBody& b, float G, float minDistance, float maxDistance) {
    // Calculate the distance between the two objects
    Vector2 d = (b.position - a.position);

    float distanceSquared = d.MagnitudeSquared();

    // Clamp the values of the distance (to allow for some insteresting visual effects)
    distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

    // Calculate the direction of the attraction force
    Vector2 attractionDirection = d.UnitVector();

    // Calculate the strength of the attraction force
    float attractionMagnitude = G * (a.mass * b.mass) / distanceSquared;

    // Calculate the final resulting attraction force vector
    Vector2 attractionForce = attractionDirection * attractionMagnitude;
    return attractionForce;
}

Vector2 Forces::GenerateSpringForce(const RigidBody& rigidRigidBody, Vector2 anchor, float restLength, float k) {
    // Calculate the distance between the anchor and the object
    Vector2 d = rigidRigidBody.position - anchor;

    // Find the spring displacement considering the rest length
    float displacement = d.Magnitude() - restLength;

    // Calculate the direction of the spring force
    Vector2 springDirection = d.UnitVector();

    // Calculate the magnitude of the spring force
    float springMagnitude = -k * displacement;
    
    // Calculate the final resulting spring force vector
    Vector2 springForce = springDirection * springMagnitude;
    return springForce;
}
