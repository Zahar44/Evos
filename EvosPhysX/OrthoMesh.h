#pragma once
#include "Mesh.h"

class OrthoMesh: public Mesh {
protected:
public:
	virtual void load(
		GLfloat* vertices,
		size_t verticesSize,
		GLuint* indices,
		size_t indicesSize
	) override;
};
