#include "InstancedMesh.h"

void InstancedMesh::generateBuffers()
{
	Mesh::generateBuffers();
	glGenBuffers(1, &modelsBuffer);
}

void InstancedMesh::load(
	GLfloat* vertices,
	size_t verticesSize,
	GLuint* indices,
	size_t indicesSize
)
{
	Mesh::load(vertices, verticesSize, indices, indicesSize);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void InstancedMesh::loadModels(glm::mat4x4* models, size_t size)
{
	glBindVertexArray(vertexArray);
	
	glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::mat4), &models[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
