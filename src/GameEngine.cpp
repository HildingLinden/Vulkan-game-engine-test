#include <iostream>
#include <numeric>

#include "GameEngine.h"

void GameEngine::init() {
	// Initialization
	graphicsEngine = std::make_unique<GraphicsEngine>();

	glfwInit();

	// Don't create a OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWmonitor *monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
	graphicsEngine->window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), monitor, nullptr);

	graphicsEngine->initVulkan(title, GraphicsEngine::PresentationMode::triple);

	glfwSetWindowUserPointer(graphicsEngine->window, this);
	
	/*
	* Callbacks
	*/
	glfwSetFramebufferSizeCallback(
		graphicsEngine->window,
		[](GLFWwindow *window, int width, int height) {
			GameEngine *gameEngine = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));
			gameEngine->graphicsEngine->framebufferResized = true;
		}
	);
	
	glfwSetMouseButtonCallback(
		graphicsEngine->window,
		[](GLFWwindow * window, int button, int action, int mods) {
			GameEngine *gameEngine = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));

			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				if (action == GLFW_PRESS) {
					gameEngine->buttonPressed = true;
				}
				else if (action == GLFW_RELEASE) {
					gameEngine->buttonPressed = false;
				}
			}
		}
	);
	
	glfwSetCursorPosCallback(
		graphicsEngine->window,
		[](GLFWwindow *window, double newMouseX, double newMouseY) {
			GameEngine *gameEngine = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));
			if (gameEngine->buttonPressed) {
				if (gameEngine->mouseX < 0) {
					gameEngine->mouseX = newMouseX;
					return;
				}
				double xDelta = newMouseX - gameEngine->mouseX;

				if (std::abs(xDelta) > 0.0) {
					gameEngine->graphicsEngine->rotateCamera(xDelta, 0.0);
				}
			}
			gameEngine->mouseX = newMouseX;
		}
	);
	
	glfwSetScrollCallback(
		graphicsEngine->window,
		[](GLFWwindow *window, double x, double y) {
			GameEngine *gameEngine = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));

			gameEngine->graphicsEngine->zoomCamera(y);
		}
	);
}



void GameEngine::run() {
	// Main game loop
	while (!glfwWindowShouldClose(graphicsEngine->window)) {
		// User events
		glfwPollEvents();

		// Render
		double frameTime = graphicsEngine->drawFrame();
		
		frameTimes.push_back(frameTime);
		timeSinceUpdate += frameTime;

		if (timeSinceUpdate > 500.0) {
			double avgFrametime = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / static_cast<double>(frameTimes.size());
			int fps = 1000 / avgFrametime;

			glfwSetWindowTitle(graphicsEngine->window, (title + " - " + std::to_string(fps) + "fps").c_str());
			//std::cout << std::to_string(fps) << "\n";

			frameTimes.clear();
			timeSinceUpdate = 0.0;
		}
	}
}

void GameEngine::cleanup() {
	graphicsEngine->cleanup();

	glfwDestroyWindow(graphicsEngine->window);
	glfwTerminate();
}
