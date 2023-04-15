#include "Physics.h"

#include <iostream>

#include "Collisions.h"
#include "RigidBody.h"
#include "Constraints.h"
#include "../Engine.h"
#include "../Graphics/Graphics.h"

std::vector<RigidBody> Physics::rigidBodies;

Physics::Physics(double const gravity) {
	this->gravity = gravity;
	rigidBodies.reserve(100);
	pixelsPerMeter = 50;
}

Physics::~Physics() {
	// delete rigidBodies;
	// for (auto rigidBody: rigidBodies) { delete rigidBody; }
	for (auto constraint: constraints) { delete constraint; }
}

RigidBody* Physics::Create(const double x, const double y, const double width, const double height, const double mass) {
	rigidBodies.emplace_back(x, y, width, height, mass);
	return &rigidBodies.at(rigidBodies.size()-1);
}

std::vector<RigidBody>* Physics::GetRigidBodies() { return &rigidBodies; }
std::vector<Constraint*>& Physics::GetConstraints() { return constraints; }
void Physics::AddConstraint(Constraint* constraint) { constraints.push_back(constraint); }
void Physics::AddForce(const Vector2& force) { forces.push_back(force); }
void Physics::AddTorque(double const torque) { torques.push_back(torque); }

void Physics::Update(double const deltaTime) {
	// Apply forces and integrate them
	for (int i = 0; i < rigidBodies.size(); i++) {
		RigidBody* rigidBody = &rigidBodies.at(i);
		Vector2 weight = Vector2(0, rigidBody->mass * gravity * pixelsPerMeter);
		rigidBody->AddForce(weight);
		for (auto force : forces) {
			rigidBody->AddForce(force);
		}

		for (auto torque : torques) {
			rigidBody->AddTorque(torque);
		}
	}
	for (int i = 0; i < rigidBodies.size(); i++) {
		RigidBody* rigidBody = &rigidBodies.at(i);
		rigidBody->IntegrateForces(deltaTime);
	}

	// Collision detection. All vs all, atm.
	std::vector<PenetrationConstraint> penetrations;
	for (int i = 0; i <= rigidBodies.size() -1; i++) {
		for (int j = i + 1; j < rigidBodies.size(); j++) {
			RigidBody* a = &rigidBodies.at(i);
			RigidBody* b = &rigidBodies.at(j);

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
	for (int i = 0; i < rigidBodies.size(); i++) {
		RigidBody* rigidBody = &rigidBodies.at(i);
		rigidBody->IntegrateVelocities(deltaTime);
	}
}






























