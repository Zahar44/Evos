#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>

class InstancedMesh : public Mesh {
private:
	GLuint modelsBuffer, normalModelsBuffer;
public:
	virtual void generateBuffers() override;

	virtual void load(
		GLfloat* vertices,
		size_t verticesSize,
		GLuint* indices,
		size_t indicesSize
	) override;

	virtual void loadModels(glm::mat4x4* models, size_t size);
};
