#pragma once

#include <vector>
#include "shapes.h"

class PhysicsSystem {
public:
	PhysicsSystem();
	void update(float elapsedTime);
	void updateObjects(std::vector<Rect> &newObjects);
	void setScreenBB(float width, float height);

private:
	std::vector<Rect> *objects;
	float boundingX, boundingY;
};