#include "Constraints.h"

#include <algorithm>


// Matrix with every inverse mass and inverse I of bodies "a" and "b"
//  [ 1/ma  0     0     0     0     0    ]
//  [ 0     1/ma  0     0     0     0    ]
//  [ 0     0     1/Ia  0     0     0    ]
//  [ 0     0     0     1/mb  0     0    ]
//  [ 0     0     0     0     1/mb  0    ]
//  [ 0     0     0     0     0     1/Ib ]
MatrixMN Constraint::GetInvM() const {
	MatrixMN invM(6, 6);
	invM.Zero();
	invM.rows[0][0] = a->inverseMass;
	invM.rows[1][1] = a->inverseMass;
    invM.rows[2][2] = a->inverseMomentOfInertia;
    invM.rows[3][3] = b->inverseMass;
	invM.rows[4][4] = b->inverseMass;
    invM.rows[5][5] = b->inverseMomentOfInertia;
	return invM;
}

// Vector with every linear and angular velocity of bodies "a" and "b"
//  [ va.x ]
//  [ va.y ]
//  [ ωa   ]
//  [ vb.x ]
//  [ vb.y ]
//  [ ωb   ]
VectorN Constraint::GetVelocities() const {
	VectorN V(6);
	V.Zero();
	V[0] = a->velocity.x;
	V[1] = a->velocity.y;
	V[2] = a->angularVelocity;
	V[3] = b->velocity.x;
	V[4] = b->velocity.y;
	V[5] = b->angularVelocity;
	return V;
}

JointConstraint::JointConstraint(): Constraint(), jacobian(1, 6), cachedLambda(1), bias(0.0) {
    cachedLambda.Zero();
}

JointConstraint::JointConstraint(RigidBody* a, RigidBody* b, const Vector2& anchorPoint): Constraint(), jacobian(1, 6), cachedLambda(1), bias(0.0) {
    this->a = a;
    this->b = b;
    this->aPoint = a->WorldToLocalSpace(anchorPoint);
    this->bPoint = b->WorldToLocalSpace(anchorPoint);
    cachedLambda.Zero();
}

void JointConstraint::PreSolve(const double dt) {
    // Get the anchor point position in world space
    const Vector2 pa = a->LocalToWorldSpace(aPoint);
    const Vector2 pb = b->LocalToWorldSpace(bPoint);

    const Vector2 ra = pa - a->position;
    const Vector2 rb = pb - b->position;

    jacobian.Zero();

    Vector2 J1 = (pa - pb) * 2.0;
    jacobian.rows[0][0] = J1.x; // A linear velocity.x
    jacobian.rows[0][1] = J1.y; // A linear velocity.y

    double J2 = ra.Cross(pa - pb) * 2.0;
    jacobian.rows[0][2] = J2;   // A angular velocity

    Vector2 J3 = (pb - pa) * 2.0;
    jacobian.rows[0][3] = J3.x; // B linear velocity.x
    jacobian.rows[0][4] = J3.y; // B linear velocity.y

    double J4 = rb.Cross(pb - pa) * 2.0;
    jacobian.rows[0][5] = J4;   // B angular velocity

    // Warm starting (apply cached lambda)
    const MatrixMN Jt = jacobian.Transpose();
    VectorN impulses = Jt * cachedLambda;

    // Apply the impulses to both bodies 
    a->ApplyLinearImpulse(Vector2(impulses[0], impulses[1])); // A linear impulse
    a->ApplyAngularImpulse(impulses[2]);                   // A angular impulse
    b->ApplyLinearImpulse(Vector2(impulses[3], impulses[4])); // B linear impulse
    b->ApplyAngularImpulse(impulses[5]);                   // B angular impulse

    // Compute the bias term (baumgarte stabilization)
    const double beta = 0.02f;
    double C = (pb - pa).Dot(pb - pa);
    C = std::max(0.0, C - 0.01);
    bias = (beta / dt) * C;
}

void JointConstraint::Solve() {
    const VectorN V = GetVelocities();
    const MatrixMN invM = GetInvM();
  
    const MatrixMN J = jacobian;
    const MatrixMN Jt = jacobian.Transpose();
    
    // Compute lambda using Ax=b (Gauss-Seidel method) 
    MatrixMN lhs = J * invM * Jt;  // A
    VectorN rhs = J * V * -1.0;   // b
    rhs[0] -= bias;
    VectorN lambda = MatrixMN::SolveGaussSeidel(lhs, rhs);
    cachedLambda += lambda;

    // Compute the impulses with both direction and magnitude
    VectorN impulses = Jt * lambda;

    // Apply the impulses to both bodies 
    a->ApplyLinearImpulse(Vector2(impulses[0], impulses[1])); // A linear impulse
    a->ApplyAngularImpulse(impulses[2]);                   // A angular impulse
    b->ApplyLinearImpulse(Vector2(impulses[3], impulses[4])); // B linear impulse
    b->ApplyAngularImpulse(impulses[5]);                   // B angular impulse
}

void JointConstraint::PostSolve() {
    // Limit the warm starting to reasonable limits
	cachedLambda[0] = std::clamp(cachedLambda[0], -10000.0, 10000.0);
}

PenetrationConstraint::PenetrationConstraint(): Constraint(), jacobian(2, 6), cachedLambda(2), bias(0.0) {
    cachedLambda.Zero();
    friction = 0.0;
}

PenetrationConstraint::PenetrationConstraint(RigidBody* a, RigidBody* b, const Vector2& aCollisionPoint, const Vector2& bCollisionPoint, const Vector2& normal): Constraint(), jacobian(2, 6), cachedLambda(2), bias(0.0) {
    this->a = a;
    this->b = b;
    this->aPoint = a->WorldToLocalSpace(aCollisionPoint);
    this->bPoint = b->WorldToLocalSpace(bCollisionPoint);
    this->normal = a->WorldToLocalSpace(normal);
    cachedLambda.Zero();
    friction = 0.0;
}

void PenetrationConstraint::PreSolve(const double dt) {
    // Get the collision points and normal in world space
    const Vector2 pa = a->LocalToWorldSpace(aPoint);
    const Vector2 pb = b->LocalToWorldSpace(bPoint);
    Vector2 n = a->LocalToWorldSpace(normal);

    const Vector2 ra = pa - a->position;
    const Vector2 rb = pb - b->position;

    jacobian.Zero();

    // Populate the first row of the Jacobian (normal vector)
    jacobian.rows[0][0] = -n.x;         // A linear velocity.x
    jacobian.rows[0][1] = -n.y;         // A linear velocity.y
    jacobian.rows[0][2] = -ra.Cross(n); // A angular velocity
    jacobian.rows[0][3] = n.x;          // B linear velocity.x
    jacobian.rows[0][4] = n.y;          // B linear velocity.y
    jacobian.rows[0][5] = rb.Cross(n);  // B angular velocity

    // Populate the second row of the Jacobian (tangent vector)
    friction = std::max(a->friction, b->friction);
    if (friction > 0.0) {
        Vector2 t = n.Normal(); // The tangent is the vector perpendicular to the normal
        jacobian.rows[1][0] = -t.x;          // A linear velocity.x
        jacobian.rows[1][1] = -t.y;          // A linear velocity.y
        jacobian.rows[1][2] = -ra.Cross(t);  // A angular velocity
        jacobian.rows[1][3] = t.x;           // B linear velocity.x
        jacobian.rows[1][4] = t.y;           // B linear velocity.y
        jacobian.rows[1][5] = rb.Cross(t);   // B angukar velocity
    }

    // Warm starting (apply cached lambda)
    const MatrixMN Jt = jacobian.Transpose();
    VectorN impulses = Jt * cachedLambda;

    // Apply the impulses to both bodies 
    a->ApplyLinearImpulse(Vector2(impulses[0], impulses[1])); // A linear impulse
    a->ApplyAngularImpulse(impulses[2]);                   // A angular impulse
    b->ApplyLinearImpulse(Vector2(impulses[3], impulses[4])); // B linear impulse
    b->ApplyAngularImpulse(impulses[5]);                   // B angular impulse

    // Compute the bias term (baumgarte stabilization)
    const double beta = 0.2f;
    double C = (pb - pa).Dot(-n);
    C = std::min(0.0, C + 0.01);
    bias = (beta / dt) * C;
}

void PenetrationConstraint::Solve() {
    const VectorN V = GetVelocities();
    const MatrixMN invM = GetInvM();
  
    const MatrixMN J = jacobian;
    const MatrixMN Jt = jacobian.Transpose();
    
    // Compute lambda using Ax=b (Gauss-Seidel method) 
    MatrixMN lhs = J * invM * Jt;  // A
    VectorN rhs = J * V * -1.0;   // b
    rhs[0] -= bias;
    VectorN lambda = MatrixMN::SolveGaussSeidel(lhs, rhs);
    
    // Accumulate impulses and clamp it within constraint limits
    VectorN oldLambda = cachedLambda;
    cachedLambda += lambda;
    cachedLambda[0] = (cachedLambda[0] < 0.0) ? 0.0 : cachedLambda[0];

    // Keep friction values between -(λn*µ) and (λn*µ)
	if (friction > 0.0) {
		const double maxFriction = cachedLambda[0] * friction;
        cachedLambda[1] = std::clamp(cachedLambda[1], -maxFriction, maxFriction);
	}
    
    lambda = cachedLambda - oldLambda;

    // Compute the impulses with both direction and magnitude
    VectorN impulses = Jt * lambda;

    // Apply the impulses to both bodies 
    a->ApplyLinearImpulse(Vector2(impulses[0], impulses[1])); // A linear impulse
    a->ApplyAngularImpulse(impulses[2]);                   // A angular impulse
    b->ApplyLinearImpulse(Vector2(impulses[3], impulses[4])); // B linear impulse
    b->ApplyAngularImpulse(impulses[5]);                   // B angular impulse
}

void PenetrationConstraint::PostSolve() {
    // TODO: Maybe clamp the values of cached lambda to reasonable limits?
}
