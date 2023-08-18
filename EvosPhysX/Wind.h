#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Random.h"
#include "Shader.h"
#include "Keyboard.h"

class Wind {
private:
	glm::vec2 direction		= { 0.0f, 0.0f };
	float amplitude			= 0.0f;
	float frequency			= 0.1f;
	float maxPower			= 1.0f;
	float maxFrequency		= 0.5f;

	float restMinTime		= 1.0f;
	float restMaxTime		= 5.0f;
	float activeMinTime		= 5.0f;
	float activeMaxTime		= 5.0f;

	float prevAmplitude		= 0.0f;

	enum State {
		TargetEmpty,
		TargetExist,
		TargetFulfilled
	};

	State state					= State::TargetEmpty;
	float targetAmplitude		= 0.0f;
	float timer					= 0.0f;
	float timePassed			= 0.0f;

	void findTarget() {
		targetAmplitude = (0.5f - Random::getRandomFloat()) * maxPower * 2.0f;
		frequency = Random::getRandomFloat() * maxFrequency;
		direction.x += (0.5f - Random::getRandomFloat()) * 2.0f;
		direction.y += (0.5f - Random::getRandomFloat()) * 2.0f;
		direction = glm::normalize(direction);
	}
public:
	void update(float delta) {
		timePassed += delta;
		if (state == State::TargetFulfilled) {
			auto chillPersent = timePassed / timer;
			amplitude = std::lerp(prevAmplitude, 0.0f, chillPersent);

			if (timePassed < timer) return;
			prevAmplitude	= 0.0f;
			amplitude		= 0.0f;
			state = State::TargetEmpty;
		}

		if (state == State::TargetEmpty) {
			findTarget();
			timer		= activeMinTime + Random::getRandomFloat() * activeMaxTime;
			timePassed	= 0.0f;
			state		= State::TargetExist;
		}

		if (state == State::TargetExist && timePassed > timer) {
			timePassed		= 0.0f;
			prevAmplitude	= targetAmplitude;
			amplitude		= targetAmplitude;

			timer = restMinTime + Random::getRandomFloat() * restMaxTime;
			state = State::TargetFulfilled;
			return;
		}

		auto timePassedPersent = timePassed / timer;
		amplitude = std::lerp(prevAmplitude, targetAmplitude, timePassedPersent);
	}

	void setUniforms(Shader* shader) {
		glUniform2fv(shader->getUniformLocation("wave.direction"), 1, glm::value_ptr(direction));
		glUniform1f(shader->getUniformLocation("wave.frequency"), frequency);
		glUniform1f(shader->getUniformLocation("wave.amplitude"), amplitude);
		glUniform1f(shader->getUniformLocation("wave.time"), (float)glfwGetTime());
	}
};
