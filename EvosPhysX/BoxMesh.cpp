#include "BoxMesh.h"

const GLfloat BoxMesh::vertices[verticesCount] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  -1.0f, -1.0f, 1.0f, // bottom-left
     0.5f, -0.5f,  0.5f,   1.0f, -1.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,   1.0f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  -1.0f,  1.0f, 1.0f, // top-left

    // Back face
    -0.5f, -0.5f, -0.5f, -1.0f, -1.0f, -1.0f, // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, -1.0f, -1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f, -1.0f, // top-right
    -0.5f,  0.5f, -0.5f, -1.0f,  1.0f, -1.0f  // top-left
};

const GLuint BoxMesh::indices[indicesCount] = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    6, 5, 4,
    4, 7, 6,

    // Left face
    3, 7, 4,
    4, 0, 3,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Top face
    3, 2, 6,
    6, 7, 3,

    // Bottom face
    5, 1, 0,
    0, 4, 5
};
