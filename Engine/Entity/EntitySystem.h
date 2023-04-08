﻿#pragma once
#include <vector>

#include "../Misc/Misc.h"
#include "Entity.h"


static std::vector<Entity> entities;

class EntitySystem
{
public:
	void Init();
	
	void CreateBoxEntity(double x, double y, double width, double height, double weight, const char* filePath);
	void CreateCircleEntity(double x, double y, double radius, double weight, const char* filePath);
	
	void Update();



	

	static int EntityCount();
	
	static Entity* CreateEntity();
	static Entity* CreateEntity(double x, double y, double width, double height, const char* imageFilePath, bool physics);
	static void DestroyEntity(int entityID);
	
	static Vector2 GetPosition(int entityID);
	static void SetPosition(int entityID, Vector2 const& position);
	
	static double GetRotation(int entityID);
	static void SetRotation(int entityID, double rotation);
	
	static Vector2 GetSize(int entityID);
	static void SetSize(int entityID, double width, double height);
	static void SetSize(int entityID, Vector2 size);
		
	static void SetTexture(int entityID, const char* filePath);
	
	static int EnablePhysics(int entityID);

	static std::vector<Sprite>* GetSprites();
	
};
