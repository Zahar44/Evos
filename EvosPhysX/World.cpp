#include "World.h"

Chunk& World::find(const std::pair<int, int>& p)
{
	auto x = (int)(p.first / Chunk::chunkSize);
	auto z = (int)(p.second / Chunk::chunkSize);
	auto& chunk = chunks[{ x, z }];

	if (chunk.views.size() == 0) {
		decorator.decorate(chunk, p.first, p.second);
	}

	return chunk;
}
