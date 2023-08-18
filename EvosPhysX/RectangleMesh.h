#pragma once

#include <physx/PxPhysics.h>
#include "OrthoMesh.h"

using namespace physx;

class RectangleMesh {
public:
    static const size_t verticesCount = 24;
    static const size_t indicesCount = 6;
    static const GLfloat vertices[verticesCount];
    static const GLuint indices[indicesCount];

    static const size_t verticesOrthoCount = 8;
    static const GLfloat verticesOrtho[verticesOrthoCount];

    static Mesh* create() {
        auto mesh = new Mesh();
        auto v = const_cast<GLfloat*>(vertices);
        auto i = const_cast<GLuint*>(indices);
        mesh->load(v, verticesCount, i, indicesCount);
        return mesh;
    }

    static OrthoMesh* createOrtho() {
        auto mesh = new OrthoMesh();
        auto v = const_cast<GLfloat*>(verticesOrtho);
        auto i = const_cast<GLuint*>(indices);
        mesh->load(v, verticesOrthoCount, i, indicesCount);
        return mesh;
    }
};
