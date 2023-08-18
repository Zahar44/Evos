#pragma once
#include "DayCycle.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sun {
private:
	DayCycle cycle;

	float ambientPower  = 0.2f;
	float diffucePower  = 0.8f;
	float specularPower = 0.2f;
	float minLerpValue  = 0.2f;

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
public:
	Sun(DayCycle _cycle):
		cycle(_cycle),
		direction(1.0f),
		ambient(1.0f),
		diffuse(1.0f),
		specular(1.0f) {}

	void update(float delta) {
		cycle.update(delta);

		float persent;
		auto state = cycle.getState(persent);
		float value = minLerpValue;

		if (state == DayCycle::Day) {
			if (persent < 0.5f) {
				value = std::lerp(minLerpValue, 1.0, persent * 2.0f);
			}
			else {
				value = std::lerp(1.0f, minLerpValue, (persent - 0.5f) * 2.0f);
			}
		}

		ambient		= glm::vec3(value) * ambientPower;
		diffuse		= glm::vec3(value) * diffucePower;
		specular	= glm::vec3(value) * specularPower;
		direction	= glm::vec3(-1 + value * 2.0f, value, -value);
	}

	void setLightUniforms(Shader* shader) {
		glUniform3fv(shader->getUniformLocation("directional.direction"), 1, glm::value_ptr(direction));
		glUniform3fv(shader->getUniformLocation("directional.ambient"), 1, glm::value_ptr(ambient));
		glUniform3fv(shader->getUniformLocation("directional.diffuse"), 1, glm::value_ptr(diffuse));
		glUniform3fv(shader->getUniformLocation("directional.specular"), 1, glm::value_ptr(specular));
	}
};
