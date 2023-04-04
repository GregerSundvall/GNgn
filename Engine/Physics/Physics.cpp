#include "Physics.h"

#include "Collisions.h"
#include "RigidBody.h"
#include "Constraints.h"
#include "../Engine.h"


Physics::Physics(double const gravity) {
	this->gravity = gravity;
}

Physics::~Physics() {
	for (auto rigidBody: rigidBodies) { delete rigidBody; }
	for (auto constraint: constraints) { delete constraint; }
}

void Physics::AddBody(RigidBody* body) {
	rigidBodies.push_back(body);
}

std::vector<RigidBody*>& Physics::GetBodies() {
	return rigidBodies;
}

void Physics::AddConstraint(Constraint* constraint) {
	constraints.push_back(constraint);	
}

std::vector<Constraint*>& Physics::GetConstraints() {
	return constraints;
}

void Physics::AddForce(const Vector2& force) {
	forces.push_back(force);
}

void Physics::AddTorque(double const torque) {
	torques.push_back(torque);
}

void Physics::Update(double deltaTime) {
	// Apply forces and integrate them
	for (auto& rigidBody : rigidBodies) {
		Vector2 weight = Vector2(0, rigidBody->mass * gravity * Engine::GetPixelsPerMeter());
		rigidBody->AddForce(weight);

		for (auto force : forces) {
			rigidBody->AddForce(force);
		}

		for (auto torque : torques) {
			rigidBody->AddTorque(torque);
		}
	}
	for (auto& rigidBody : rigidBodies) {
		rigidBody->IntegrateForces(deltaTime);
	}

	// Collision detection. All vs all, for now.
	std::vector<PenetrationConstraint> penetrations;
	for (int i = 0; i <= rigidBodies.size() -1; ++i) {
		for (int j = 0; j < rigidBodies.size(); ++j) {
			RigidBody* a = rigidBodies[i];
			RigidBody* b = rigidBodies[j];

			std::vector<Contact> contacts;
			if (Collisions::IsColliding(a, b, contacts)) {
				for (auto contact : contacts) {
					PenetrationConstraint penetration(contact.a, contact.b,
						contact.start, contact.end, contact.normal);
					penetrations.push_back(penetration);
				}
			}
		}
	}

	// Solve collisions
	for (auto& constraint : constraints) {
		constraint->PreSolve(deltaTime);
	}
	for (auto& penetration : penetrations) {
		penetration.PreSolve(deltaTime);
	}
	for (int i = 0; i < iterationCount; ++i) {
		for (auto& constraint : constraints) {
			constraint->Solve();
		}
		for (auto& penetration : penetrations) {
			penetration.Solve();
		}
	}
	for (auto& constraint : constraints) {
		constraint->PostSolve();
	}
	for (auto& penetration : penetrations) {
		penetration.PostSolve();
	}

	// Integrate velocities
	for (auto& rigidBody : rigidBodies) {
		rigidBody->IntegrateVelocities(deltaTime);
	}
}


































