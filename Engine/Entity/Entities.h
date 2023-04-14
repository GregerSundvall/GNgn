#pragma once
#include <vector>

#include "../Misc/Misc.h"
#include "Entity.h"




class Entities
{
	static std::vector<Entity>* entities;
public:
	static void Init();
	
	static Entity* Create(double x, double y, double width, double height, double mass, const char* imageFilePath);
	// static void Create(double x, double y, double radius, double mass, const char* filePath);

	static void Update();


	static int EntityCount();
	static void UpdateSprites();

	
	// static Entity* Create();
	// static void DestroyEntity(int entityID);
	//
	// static Vector2 GetPosition(int entityID);
	// static void SetPosition(int entityID, Vector2 const& position);
	//
	// static double GetRotation(int entityID);
	// static void SetRotation(int entityID, double rotation);
	//
	// static Vector2 GetSize(int entityID);
	// static void SetSize(int entityID, double width, double height);
	// static void SetSize(int entityID, Vector2 size);
	// 	
	// static void SetTexture(int entityID, const char* filePath);
	//
	// static int EnablePhysics(int entityID);
	//
	// static std::vector<Sprite>* GetSprites();
	
};
