#pragma once

#include <memory>

#include "graphicsEngine.h"

class GameEngine {
public:
	std::unique_ptr<GraphicsEngine> graphicsEngine;
	void init();
	void run();
	void cleanup();
};