#pragma once
#include <physx/PxPhysicsAPI.h>
#include "World.h"
#include "Player.h"
#include "RigidView.h"
#include "CylinderMesh.h"

using namespace physx;

class Game
{
private:
	PxDefaultAllocator		allocator;
	PxDefaultErrorCallback	errorCallback;
	PxFoundation*			foundation		= NULL;
	PxPhysics*				physics			= NULL;
	PxDefaultCpuDispatcher* dispatcher		= NULL;
	PxScene*				scene			= NULL;
	PxMaterial*				material		= NULL;
	World*					world			= NULL;

	Player* createPlayer();
public:
	PxReal simulationTime = 1.f / 60.f;
	~Game();

	void initialize();
	void simulate();
	void update(float delta);
	World* getWorld() { return world; };
};
