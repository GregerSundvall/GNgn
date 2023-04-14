#pragma once

#include <SDL_shape.h>
#include <vector>

#include "Transform.h"
#include "../Misc/Misc.h"
#include "../Misc/Vector2.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Shapes.h"



class Entity
{
		
public:
	RigidBody* rigidBody;
	SDL_Texture* texture;
	// Creates a box entity
	Entity(double x, double y, double width, double height, double mass, const char* filePath);
	// Circle entity
	// Entity(double x, double y, double radius, double weight, const char* filePath);
	
	// virtual void Update(double deltaTime);
	
	// void SetPosition(Vector2 const position);
	// void SetPosition(double x, double y);
	// void SetRotation(double rotation);
	// void SetMass(double weight);
	// void SetTexture(const char* filePath);
	//
	// void SetShape(double width, double height);
	// void SetShape(double radius);
	// void SetBoxWidth(double width);
	// void SetBoxHeight(double height);
	// void SetDiameter(double diameter);
	//
	// Vector2 GetPosition();
	// double GetRotation();
	// double GetMass();
	//
	// ShapeType GetShapeType();
	// Vector2 GetBoxSize();
	// double GetDiameter();

};


