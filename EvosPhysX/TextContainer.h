#pragma once
#include "ContainerView.h"
#include "TextView.h"

class TextContainer: public ContainerView {
private:
	TextView text;

	glm::vec2 getTextAllowedRange(glm::mat4& model) {
		glm::vec2 center = { model[3].x, model[3].y };
		glm::vec2 scale = { model[0].x, model[1].y };

		return {
			center.x + scale.x / 2.0f,
			center.y - scale.y / 2.0f
		};
	}
public:
	TextContainer(
		TextView _text,
		Shader* _shader = Shader::get(Shader::PrimitiveOrtho)
	):
		ContainerView(_shader), text(_text) {
		setLayer(2.0f);
		setColor({ 0.0f, 0.0f, 1.0f });
		text.setLayer(1.0f);
	}

	TextView& getTextView() { return text; }

	virtual void draw() override {
		auto s = std::sinf(glfwGetTime()) + 1.0f;
		setScale({ s * 300.0f, s * 300.0f });

		auto model = calculateModel();
		ContainerView::draw(model);

		auto range = getTextAllowedRange(model);
		text.draw(range);
	}
};
