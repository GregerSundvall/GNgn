#pragma once

#include "../Misc/Vector2.h"


class Entity
{
	int entityID = -1;
	int transformID = -1;
	int textureID = -1;
	int rigidBodyID = -1; 
public:
	explicit Entity(int entityID);
	Entity(int entityID, double x, double y, double width, double height, const char* filePath);

	virtual void Update(double deltaTime);
	
	Vector2 GetPosition();
	void SetPosition(Vector2 position);

	double GetRotation();
	void SetRotation(double rotation);
	
	Vector2 GetSize();
	void SetSize(Vector2 size);
	
	void SetTexture(const char* filePath);
	
	int GetEntityID() const;
	int GetTransformID() const;
	int GetRigidBodyID() const;
	int GetTextureID() const;
};


