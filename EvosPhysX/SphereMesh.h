#pragma once
#include <physx/PxPhysics.h>
#include "InstancedMesh.h"
#include <corecrt_math_defines.h>

class SphereMesh {
private:
    static std::vector<GLfloat> vertices;
    static std::vector<GLuint> indices;
public:

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

    static void createRaw(int rings, int sectors) {
        float const R = 1. / (float)(rings - 1);
        float const S = 1. / (float)(sectors - 1);
        int r, s;

        vertices.resize(rings * sectors * 3 * 2);
        auto it = vertices.begin();
        for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            *it++ = x;
            *it++ = y;
            *it++ = z;

            *it++ = x;
            *it++ = y;
            *it++ = z;
        }

        indices.resize(rings * sectors * 6);
        auto i = indices.begin();
        for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = (r + 1) * sectors + s;
            *i++ = (r + 1) * sectors + (s + 1);

            *i++ = r * sectors + s;
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = r * sectors + (s + 1);
        }
    }
};
