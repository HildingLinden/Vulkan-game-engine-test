#include "engine.h"
#include "shapes.h"

#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

int main() {
	std::string title("Vulkan Test Application - ");

	Engine app(800, 600, title);

	try {
		app.init();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	Rect rect1(50, 50, 100, 100);
	app.addRect(rect1);

	Rect rect2(300, 300, 10, 10);
	app.addRect(rect2);

	uint32_t frameCount = 0;
	float time = 0.0f;
	size_t fpsIndex = 0;

	std::array<float, 10> fpsBuffer{};
	fpsBuffer.fill(144.0f);

	while (!app.shouldClose()) {
		app.pollEvents();

		frameCount++;

		std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();

		try {
			app.drawFrame();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
		std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
		time += std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		if (time > 0.5f) {
			rect1.modelMatrix = glm::translate(rect1.modelMatrix, glm::vec3(10.0f, 0.0f, 0.0f));
			app.updateMatrix(rect1);

			fpsBuffer[fpsIndex++ % 10] = frameCount / time;

			float avgFps = 0.0f;
			for (float fps : fpsBuffer) {
				avgFps += fps;
			}
			avgFps /= 10;

			std::string fpsString = title + std::to_string((int)round(avgFps)) + " fps";

			time = 0.0f;
			frameCount = 0;

			app.changeTitle(fpsString);
		}
	}

	try {
		app.cleanup();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}