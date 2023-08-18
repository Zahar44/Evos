#pragma once
#include <physx/PxPhysicsAPI.h>
#include "InstancedView.h"
#include "Tree.h"
#include "Chunk.h"
#include "Random.h"
#include "PerlinNoise.hpp"
#include "CylinderMesh.h"
#include "SphereMesh.h"

using namespace physx;


class TreeGenerator {
private:
	PxPhysics* physics;
	PxScene* scene;
	PxShape* coreShape;
	PxMaterial* coreMaterial;
	siv::PerlinNoise noise;

	glm::mat4x4 getTreeCoreModel(
		float worldX,
		float worldZ
	) {
		auto hight = 1 + Random::getRandomFloat() * 2.0f;

		glm::mat4x4 model(1.0f);
		model = glm::translate(model, { worldX, hight, worldZ });
		model = glm::scale(model, { 0.4f, hight, 0.4f });

		return model;
	}

	glm::mat4x4 getTreeLeavesModel(
		glm::mat4x4& coreModel,
		float random
	) {
		glm::mat4x4 leavesModel(1.0f);
		auto extend = random * 3.0f;
		glm::vec3 extendVector = { extend, extend + random * 2.0f, extend };

		glm::vec3 translate = {
			coreModel[3][0],
			coreModel[3][1] + coreModel[1][1] + extendVector.y / 2.0f,
			coreModel[3][2]
		};
		leavesModel = glm::translate(leavesModel, translate);

		leavesModel = glm::scale(leavesModel, extendVector);

		return leavesModel;
	}

	void addTreeModels(
		InstancedView* coreView,
		InstancedView* leavesView,
		float worldX,
		float worldZ,
		float random
	) {
		auto coreModel = getTreeCoreModel(worldX, worldZ);
		auto leavesModel = getTreeLeavesModel(coreModel, random);

		coreView->addModel(coreModel);
		leavesView->addModel(leavesModel);

		auto coreTransform = PxTransform(PxVec3(coreModel[3].x, coreModel[3].y, coreModel[3].z));
		auto coreActor = physics->createRigidStatic(coreTransform);
		if (coreActor) {
			coreActor->attachShape(*coreShape);
			scene->addActor(*coreActor);
		}
	}
public:

	TreeGenerator(PxPhysics* _physics, PxScene* _scene, siv::PerlinNoise _noise):
		physics(_physics), scene(_scene), noise(_noise) {
		coreMaterial = physics->createMaterial(0.0f, 0.0f, 0.0f);
		coreShape = physics->createShape(PxSphereGeometry(1.0f), *coreMaterial);
	}

	void generate(Chunk& chunk, float worldX, float worldZ, float density) {
		int xStart	= worldX - Chunk::greedSize * Chunk::greedsHalfCount;
		int zStart	= worldZ - Chunk::greedSize * Chunk::greedsHalfCount;
		int xEnd	= worldX + Chunk::greedSize * Chunk::greedsHalfCount;
		int zEnd	= worldZ + Chunk::greedSize * Chunk::greedsHalfCount;

		auto coreMesh = CylinderMesh::createInstanced();
		auto coreView = new InstancedView(Shader::get(Shader::Type::Instanced), coreMesh);
		coreView->setColor({ 0.2f, 0.2f, 0.2f });
		auto leavesMesh = SphereMesh::createInstanced();
		auto leavesView = new InstancedView(Shader::get(Shader::Type::WaveInstanced), leavesMesh);
		leavesView->setColor({ 0.0f, 1.0f, 0.0f });
		bool any = false;

		for (int x = xStart; x < xEnd; x += Chunk::greedSize)
		{
			for (int z = zStart; z < zEnd; z += Chunk::greedSize)
			{
				float greedCenterX = x + Chunk::greedHalfSize;
				float greedCenterZ = z + Chunk::greedHalfSize;
				auto random = noise.noise2D_01(
					greedCenterX / Chunk::chunkSize,
					greedCenterZ / Chunk::chunkSize
				);

				if (random < density) continue;
				any = true;

				addTreeModels(
					coreView,
					leavesView,
					greedCenterX,
					greedCenterZ,
					random
				);
			}
		}

		if (!any) return;
		chunk.views.push_back(coreView);
		chunk.views.push_back(leavesView);
	}
};
