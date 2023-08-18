#pragma once
#include <vector>
#include "IView.h"
#include "IWorldObject.h"

struct Chunk
{
public:
	static const int chunkSize			= 32;
	static const int chunkHalfSize		= (int)(chunkSize / 2);
	static const int greedsCount		= 8;
	static const int greedsHalfCount	= (int)(greedsCount / 2);
	static const int greedSize			= (int)(chunkSize / greedsCount);
	static const int greedHalfSize		= (int)(greedSize / 2);

	std::vector<IView*> views;
	std::vector<IWorldObject*> statics;
};
