#pragma once
#include <physx/PxPhysics.h>
#include "InstancedMesh.h"
#include <corecrt_math_defines.h>

class CylinderMesh {
private:
    static std::vector<GLfloat> vertices;
    static std::vector<GLuint> indices;
public:
    static const int segmentsCount = 32;

    static Mesh* create() {
        auto mesh = new Mesh();

        mesh->load(vertices.data(), vertices.size(), indices.data(), indices.size());
        return mesh;
    }

    static InstancedMesh* createInstanced() {
        auto mesh = new InstancedMesh();

        mesh->load(vertices.data(), vertices.size(), indices.data(), indices.size());
        return mesh;
    }

    static void createRaw() {
        float angleIncrement = 2.0f * M_PI / static_cast<float>(segmentsCount);

        int vertexCount = (segmentsCount + 1) * 4;  // 4 vertices per segment
        vertices.reserve(vertexCount * 3);  // Reserve memory for x, y, z of each vertex
        indices.reserve(segmentsCount * 12);  // Reserve memory for indices

        for (int i = 0; i <= segmentsCount; ++i) {
            float angle = i * angleIncrement;
            float x = std::cos(angle);
            float z = std::sin(angle);

            vertices.push_back(x);
            vertices.push_back(-1.0f);
            vertices.push_back(z);

            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(z);

            vertices.push_back(x);
            vertices.push_back(1.0f);
            vertices.push_back(z);

            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(z);
        }

        // Create indices for the side faces
        for (int i = 0; i < segmentsCount; ++i) {
            indices.push_back(i * 2);
            indices.push_back(i * 2 + 1);
            indices.push_back((i + 1) * 2 + 1);

            indices.push_back(i * 2);
            indices.push_back((i + 1) * 2 + 1);
            indices.push_back((i + 1) * 2);
        }

        // Create indices for the bottom face
        for (int i = 0; i < segmentsCount; ++i) {
            indices.push_back(vertices.size() / 2);  // Center vertex
            indices.push_back(i * 2);
            indices.push_back((i + 1) * 2);
        }

        // Create indices for the top face
        for (int i = 0; i < segmentsCount; ++i) {
            indices.push_back(vertices.size() / 2 + 1);  // Center vertex
            indices.push_back((i + 1) * 2 + 1);
            indices.push_back(i * 2 + 1);
        }
    }
};
