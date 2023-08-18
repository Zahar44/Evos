#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

class Mesh {
protected:
	GLuint vertexArray, vertexBuffer, elementsBuffer;
	GLuint indicesCount;

	virtual void generateBuffers();
public:
	virtual void load(GLfloat* vertices, size_t verticesSize, GLuint* indices, size_t indicesSize);
	void bind();
	void clear();
	GLuint getElementsCount() { return indicesCount; }
};
