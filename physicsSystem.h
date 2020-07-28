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

	bool sweptAABB(Rect &staticRect, Rect &currentRect, float velX, float velY, float &normalX, float &normalY, float &time);
};