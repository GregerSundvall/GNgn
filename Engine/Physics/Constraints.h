#pragma once
#include "RigidBody.h"
#include "../Misc/Vector2.h"
#include "../Misc/VectorN.h"
#include "../Misc/MatrixMN.h"



class Constraint {
public:
	RigidBody* a;
	RigidBody* b;

	Vector2 aPoint; // The constraint point in A's local space
	Vector2 bPoint; // The constraint point in B's local space

	virtual ~Constraint() = default;

	MatrixMN GetInvM() const;
	VectorN GetVelocities() const;

	virtual void PreSolve(const double dt) {}
	virtual void Solve() {}
	virtual void PostSolve() {}
};

class JointConstraint: public Constraint {
private:
	MatrixMN jacobian;
	VectorN cachedLambda;
	double bias;
    
public:
	JointConstraint();
	JointConstraint(RigidBody* a, RigidBody* b, const Vector2& anchorPoint);
	void PreSolve(const double dt) override;
	void Solve() override;
	void PostSolve() override;
};

class PenetrationConstraint: public Constraint {
private:
	MatrixMN jacobian;
	VectorN cachedLambda;
	double bias;
	Vector2 normal;    // Normal direction of the penetration in A's local space
	double friction; // Friction coefficient between the two penetrating bodies
        
	public:
	PenetrationConstraint();
	PenetrationConstraint(RigidBody* a, RigidBody* b, const Vector2& aCollisionPoint, const Vector2& bCollisionPoint, const Vector2& normal);
	void PreSolve(const double dt) override;
	void Solve() override;
	void PostSolve() override;
};
