#pragma once
#include <physx/PxPhysics.h>
#include <physx/PxRigidDynamic.h>

using namespace physx;

class MovementStrategy {
public:
	enum MovementDirection {
		None	= 0x00000000,
		Up		= 0x00000001,
		Left	= 0x00000010,
		Right	= 0x00000100,
		Down	= 0x00001000
	};

	static void moveInDirection(
		PxRigidDynamic* actor,
		int direction,
		float speed
	) {
		if (direction == MovementDirection::None) {
			return;
		}

		PxVec3 velocity(0.0f);
		if (direction & MovementDirection::Up) {
			velocity.z -= speed;
		}
		if (direction & MovementDirection::Left) {
			velocity.x -= speed;
		}
		if (direction & MovementDirection::Right) {
			velocity.x += speed;
		}
		if (direction & MovementDirection::Down) {
			velocity.z += speed;
		}
		actor->setLinearVelocity(velocity);
	}
};
