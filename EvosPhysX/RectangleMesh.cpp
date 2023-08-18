#include "RectangleMesh.h"

const GLfloat RectangleMesh::vertices[] = {
    -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-left
     0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, // top-left
     0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f  // top-right
};

const GLfloat RectangleMesh::verticesOrtho[] = {
    -0.5f,  0.5f,
     0.5f,  0.5f,
    -0.5f, -0.5f,
     0.5f, -0.5f
};

const GLuint RectangleMesh::indices[] = {
    2, 1, 0,
    2, 3, 1,
};
