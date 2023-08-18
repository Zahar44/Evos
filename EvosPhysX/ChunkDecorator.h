#pragma once
#include <physx/PxPhysicsAPI.h>
#include "PerlinNoise.hpp"
#include "GroundGenerator.h"
#include "TreeGenerator.h"
#include <thread>

using namespace physx;

class ChunkDecorator {
private:
	const float scale = std::powf(2.0f, 5.0f);
	siv::PerlinNoise perlin;
	GroundGenerator ground;
	TreeGenerator tree;
public:
	ChunkDecorator(PxPhysics* _physics, PxScene* _scene):
		perlin(1.0f), tree(_physics, _scene, perlin) {}

	void decorate(Chunk& chunk, float x, float z) {
		ground.generate(chunk, x, z);
		tree.generate(chunk, x, z, 0.5f);
	}
};
