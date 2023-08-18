#pragma once
#include "View.h"
#include "RectangleMesh.h"
#include "Chunk.h"
#include "Random.h"

class GroundGenerator {
public:
	void generate(Chunk& chunk, float worldX, float worldZ) {
        auto view = new View(Shader::get(), RectangleMesh::create());
        view->translate({ worldX, 0, worldZ });
        view->scale({ Chunk::chunkSize, Chunk::chunkSize, Chunk::chunkSize });
        view->setColor({
            0.0f,
            Random::getRandomFloat() / 2.0f + 0.5f,
            0.0f
            });
        chunk.views.push_back(view);
	}
};
