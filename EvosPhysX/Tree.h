#pragma once
#include "IView.h"
#include "IWorldObject.h"

class Tree: public IWorldObject {
private:
	std::vector<IView*> viewes;
public:
	Tree(std::vector<IView*> _viewes):
		viewes(_viewes) {}

	std::vector<IView*>& getViewes() {
		return viewes;
	}
};
