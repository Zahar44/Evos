#pragma once
#include "MetricsView.h"
#include "ContainerView.h"
#include "Mouse.h"

class UIModule {
private:
	std::vector<ContainerView*> views;

	ContainerView* active = nullptr;
	Mouse mouse;

	bool inRange(ContainerView* view, const glm::dvec2& position) {
		return (
			position.x > view->getOffset().x &&
			position.x < view->getOffset().x + view->getScale().x &&
			position.y > view->getOffset().y &&
			position.y < view->getOffset().y + view->getScale().y
		);
	}
public:
	~UIModule() {
		for (auto& view : views) {
			delete view;
			view = nullptr;
		}
	}

	void initialize() {
		views.push_back(new MetricsView());
	}

	void draw() {
		auto pressed = mouse.isKeyPressed(GLFW_MOUSE_BUTTON_1);
		auto& position = mouse.getPosition();
		auto positionOffset = mouse.getPositionOffset();

		if (active) {
			if (pressed || inRange(active, position)) {
				active->onMouseHower(position, positionOffset, pressed);
			}
			else {
				active->onMouseLeft(position, pressed);
				active = nullptr;
			}
		}

		for (auto& view : views) {
			if (!active && inRange(view, position)) {
				view->onMouseEnter(position, pressed);
				active = view;
			}

			view->draw();
		}
	}
};
