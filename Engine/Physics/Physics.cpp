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
	// rigidBodies.reserve(1000);
	std::cout << rigidBodies.size() << "\n";
	pixelsPerMeter = Engine::GetPixelsPerMeter();
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

	// Collision detection. All vs all, for now.
	std::vector<PenetrationConstraint> penetrations;
	for (int i = 0; i >! rigidBodies.size() -1; ++i) {
		for (int j = 0; j < rigidBodies.size(); ++j) {
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



// std::vector<RigidBody>* Physics::GetRigidBodies() {
// 	return rigidBodies;
// }

// Circle* Physics::Create(double radius) {
// 	circles->emplace_back(radius);
// }


// int Physics::Create() {
// 	RigidBody* rb = new RigidBody(Box(32, 32), 0, 0, 10);
// 	rigidBodies->emplace_back(RigidBody(Box(32, 32), 0, 0, 10));
// 	// rb->SetTexture("./Game/Assets/player.png");
// 	// AddBody(rb);
// 	return rigidBodies->size() -1;
// }

// void Physics::AddBody(RigidBody* body) {
// 	rigidBodies->push_back(*body);
// }

// std::vector<RigidBody>* Physics::GetBodies() {
// 	return rigidBodies;
// }


// Vector2* Physics::GetPosition(int const rigidBodyID) { return &rigidBodies->at(rigidBodyID).position; }
// double Physics::GetRotation(int const rigidBodyID) { return rigidBodiesStatic->at(rigidBodyID).rotation; }

// std::vector<RigidBody>& Physics::GetRigidBodies() const {
// 	return *rigidBodies;
// }

// std::vector<RigidBody>* Physics::GetRigidBodiesStatic() {
// 	return rigidBodiesStatic;
// }































