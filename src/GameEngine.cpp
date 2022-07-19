#include <iostream>

#include "GameEngine.h"

void GameEngine::init() {
	const uint32_t WIDTH = 1920;
	const uint32_t HEIGHT = 1080;
	const std::string title("Vulkan Test Application");

	// Initialization
	graphicsEngine = std::make_unique<GraphicsEngine>();

	glfwInit();

	// Don't create a OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	graphicsEngine->window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(graphicsEngine->window, this);
	glfwSetFramebufferSizeCallback(
		graphicsEngine->window,
		[](GLFWwindow *window, int width, int height) {
			GraphicsEngine *graphicsEngine = reinterpret_cast<GraphicsEngine *>(glfwGetWindowUserPointer(window));
			graphicsEngine->framebufferResized = true;
		}
	);

	graphicsEngine->initVulkan("Vulkan game engine", GraphicsEngine::PresentationMode::triple);
}

void GameEngine::run() {
	// Main game loop
	while (!glfwWindowShouldClose(graphicsEngine->window)) {
		// User events
		glfwPollEvents();

		// Render
		graphicsEngine->drawFrame();
	}
}

void GameEngine::cleanup() {
	graphicsEngine->cleanup();

	glfwDestroyWindow(graphicsEngine->window);
	glfwTerminate();
}
