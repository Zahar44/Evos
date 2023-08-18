#pragma once
#include "IView.h"
#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

class View : public IView {
protected:
	Shader* shader;
	Mesh* mesh;
	glm::mat4x4 modelMatrix;
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };

	bool shouldRecalculateNormalMatrix = true;
public:
	View(
		Shader* _shader,
		Mesh* _mesh
	):
		mesh(_mesh),
		shader(_shader),
		modelMatrix(1.0f)
	{};
	~View() {
		mesh->clear();
		delete mesh;
	}

	virtual void draw() override {
		shader->useProgram();
		mesh->bind();

		glUniformMatrix4fv(
			shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniform3fv(
			shader->getUniformLocation("color"), 1, glm::value_ptr(color));

		glDrawElements(GL_TRIANGLES, mesh->getElementsCount(), GL_UNSIGNED_INT, 0);
	}

	virtual void translate(const glm::vec3& value) {
		modelMatrix = glm::translate(modelMatrix, value);
	}

	virtual void scale(const glm::vec3& value) {
		modelMatrix = glm::scale(modelMatrix, value);
	}

	virtual glm::vec3 getTranslation() {
		return {
			modelMatrix[3][0],
			modelMatrix[3][1],
			modelMatrix[3][2]
		};
	}

	virtual glm::vec3 getScale() {
		return {
			modelMatrix[0][0],
			modelMatrix[1][1],
			modelMatrix[2][2]
		};
	}

	void setColor(glm::vec3 _color) {
		color = _color;
	}
};
