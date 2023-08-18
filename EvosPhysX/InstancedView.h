#pragma once
#include "IView.h"
#include "InstancedMesh.h"
#include <glm/gtc/type_ptr.hpp>

class InstancedView: public IView {
protected:
	Shader* shader;
	InstancedMesh* mesh;
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };
	std::vector<glm::mat4x4> models;
	bool shouldLoadMeshModels = false;
public:
	InstancedView(
		Shader* _shader,
		InstancedMesh* _mesh
	) :
		mesh(_mesh),
		shader(_shader)
	{};
	~InstancedView() {
		mesh->clear();
		delete mesh;
	}

	virtual void draw() override {
		shader->useProgram();
		mesh->bind();

		if (shouldLoadMeshModels) {
			shouldLoadMeshModels = false;
			mesh->loadModels(models.data(), models.size());
		}

		glUniform3fv(
			shader->getUniformLocation("color"), 1, glm::value_ptr(color));
		glDrawElementsInstanced(
			GL_TRIANGLES, mesh->getElementsCount(), GL_UNSIGNED_INT, 0, models.size());
	}

	void setColor(glm::vec3 _color) {
		color = _color;
	}

	void addModel(glm::mat4x4 model) {
		models.push_back(model);
		shouldLoadMeshModels = true;
	}
};
