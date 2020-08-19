#pragma once

#include <vector>
#include "shapes.h"

class PhysicsSystem {
public:
	PhysicsSystem(std::vector<Rect> *objects);
	void update(float elapsedTime);
	void setScreenBB(float width, float height);

private:	
	std::vector<Rect>* objects = nullptr;

	float boundingX = 0.0f;
	float boundingY = 0.0f;

	bool sweptAABB(Rect &staticRect, Rect &currentRect, float velX, float velY, float &normalX, float &normalY, float &time);
};