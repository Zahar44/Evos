#pragma once
#include <unordered_map>
#include <physx/PxPhysicsAPI.h>

#include "Chunk.h"
#include "ChunkDecorator.h"
#include "Sun.h"
#include "Wind.h"
#include "Player.h"

using namespace physx;

struct PairHash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		// Combine the hash values of the pair's elements
		return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
	}
};

struct PairEqual {
	template <class T1, class T2>
	bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};

class World
{
private:
	std::unordered_map<std::pair<int, int>, Chunk, PairHash, PairEqual> chunks;

	PxPhysics* physics;
	PxScene* scene;
	Player* player;
	Sun sun;
	Wind wind;

	ChunkDecorator decorator;
public:
	World(PxPhysics* _physics, Player* _player, PxScene* _scene):
		physics(_physics),
		player(_player),
		scene(_scene),
		sun(DayCycle(100.0f, 0.1f)),
		decorator(_physics, _scene) {}
	~World() {
		for (auto& pair : chunks) {
			for (auto& view : pair.second.views) {
				delete view;
				view = nullptr;
			}
			pair.second.views.clear();
		}
		delete player;
		chunks.clear();
	}

	Chunk& find(const std::pair<int, int>& p);

	Sun& getSun() { return sun; }
	Wind& getWind() { return wind; }
	Player& getPlayer() { return *player; }
};
