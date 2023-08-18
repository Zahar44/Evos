#pragma once
#include <physx/PxPhysics.h>
#include "InstancedMesh.h"

using namespace physx;

class BoxMesh {
public:
    static const size_t verticesCount = 48;
    static const size_t indicesCount = 36;
    static const GLfloat vertices[verticesCount];
    static const GLuint indices[indicesCount];

	static Mesh* create() {
        auto mesh = new Mesh();
        auto v = const_cast<GLfloat*>(vertices);
        auto i = const_cast<GLuint*>(indices);
        mesh->load(v, verticesCount, i, indicesCount);
        return mesh;
	}

    static InstancedMesh* createInstanced() {
        auto mesh = new InstancedMesh();
        auto v = const_cast<GLfloat*>(vertices);
        auto i = const_cast<GLuint*>(indices);
        mesh->load(v, verticesCount, i, indicesCount);
        return mesh;
    }
};
