#pragma once

#include <memory>
#include <string>

#include "graphicsEngine.h"

class GameEngine {
public:
	const uint32_t WIDTH = 1920;
	const uint32_t HEIGHT = 1080;
	const bool fullscreen = false;

	std::unique_ptr<GraphicsEngine> graphicsEngine;
	bool buttonPressed = false;
	double mouseX = -1.0, mouseY = -1.0;
	double timeSinceUpdate = 0.0;
	std::vector<double> frameTimes;
	const std::string title{ "Vulkan Test Application" };

	void init();
	void run();
	void cleanup();
};