#pragma once

#include <vector>

#include "shapes.h"
#include "graphicsEngine.h"

class GameObjects {
public:
	std::vector<Rect> rects;
	std::vector<Rect> newRects;

	GraphicsEngine *graphicsEnginePtr;

	GameObjects(GraphicsEngine *graphicsEnginePtr);
	void addRect(float x, float y, float width, float height, std::string texture, bool isStatic = true);
	void checkNewRects();
};