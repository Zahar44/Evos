#pragma once
#include <physx/PxPhysicsAPI.h>
#include "View.h"

using namespace physx;

class RigidView: public View {
private:
	const PxRigidDynamic* actor;

	void updateModel() {
		auto pos = actor->getGlobalPose();

		// Convert the PxTransform to a 4x4 matrix
		PxMat44 pxTransform(pos);

		// OpenGL expects the matrix in column-major order, so we need to transpose it
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				modelMatrix[j][i] = pxTransform[j][i];
			}
		}
	}
public:
	RigidView(
		const PxRigidDynamic* _actor,
		Shader* _shader,
		Mesh* _mesh
	):
		View(_shader, _mesh),
		actor(_actor)
	{};

	virtual void draw() override {
		updateModel();
		View::draw();
	}
};
