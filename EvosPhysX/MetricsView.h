#pragma once
#include "Metric.h"
#include "TextView.h"
#include "TextContainer.h"

class MetricsView: public TextContainer {
private:
public:
	MetricsView(): TextContainer(TextView()) {
		setScale({ 250.0f, 400.0f });
	}

	virtual void draw() override {
		std::string str;
		for (auto& snapshot : Metric::getLastSnapshots()) {
			
			str += snapshot.first;
			str += ": ";
			str += std::to_string(snapshot.second.elapsed());
			str += '\n';
		}

		getTextView().setText(str);

		TextContainer::draw();
	}
};
