#pragma once
#include <physx/PxPhysics.h>
#include <GLFW/glfw3.h>
#include "IView.h"
#include "Keyboard.h"
#include "MovementStrategy.h"

using namespace physx;

class Player {
private:
	IView* view;
	PxRigidDynamic* actor;
	Keyboard keyboard;
	float speed = 10.0f;
	float fastSpeed = 1000.0f;

	void handleMovement(float delta) {
		int direction = MovementStrategy::None;

		if (keyboard.isKeyPressed(GLFW_KEY_W)) {
			direction += MovementStrategy::Up;
		}
		if (keyboard.isKeyPressed(GLFW_KEY_A)) {
			direction += MovementStrategy::Left;
		}
		if (keyboard.isKeyPressed(GLFW_KEY_D)) {
			direction += MovementStrategy::Right;
		}
		if (keyboard.isKeyPressed(GLFW_KEY_S)) {
			direction += MovementStrategy::Down;
		}
		if (keyboard.isKeyPressed(GLFW_KEY_R)) {
			auto pos = actor->getGlobalPose();
			pos.p.x = 0;
			pos.p.y = 5;
			pos.p.z = 0;
			actor->setGlobalPose(pos);
		}

		auto speedValue = keyboard.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? fastSpeed : speed;
		MovementStrategy::moveInDirection(actor, direction, speedValue);
	}
public:
	Player(
		IView* _view,
		PxRigidDynamic* _actor
	): view(_view), actor(_actor) {}
	
	IView* getView() { return view; }
	PxRigidDynamic* getActor() { return actor; }

	void update(float delta) {
		handleMovement(delta);
	}

	const glm::vec3 getPosition() {
		const auto& transform = actor->getGlobalPose().p;
		return { transform.x, transform.y, transform.z };
	}
};
