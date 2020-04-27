#include "engine.h"
#include "shapes.h"

#include <iostream>
#include <string>
#include <cstdlib>

int main() {
	try {
		std::string title("Vulkan Test Application - ");

		Engine app(1280, 720, title, ShaderBufferTypes::SSBO);

		app.init();

		uint32_t frameCount = 0;
		float time = 0.0f;
		float elapsedTime = 0.0f;
		size_t fpsIndex = 0;

		std::array<float, 10> fpsBuffer{};
		fpsBuffer.fill(144.0f);

		Rect r(10, 10, 100, 100);
		app.addRect(r);

		while (!app.shouldClose()) {
			std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();

			// User input
			app.pollEvents();
			if (app.checkMouseClick()) {
				Rect tmp(rand() % 1280, rand() % 720, 10, 10);
				app.addRect(tmp);
			}

			// Render
			app.drawFrame();
			frameCount++;

			std::chrono::time_point currentTime = std::chrono::high_resolution_clock::now();
			elapsedTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
			time += elapsedTime;

			if (time > 0.5f) {
				fpsBuffer[fpsIndex++ % 10] = frameCount / time;

				float avgFps = 0.0f;
				for (float fps : fpsBuffer) {
					avgFps += fps;
				}
				avgFps /= 10;

				std::string fpsString = title + std::to_string((int)round(avgFps)) + " fps - " + std::to_string(app.rectCount) + " rectangles";

				time = 0.0f;
				frameCount = 0;

				app.changeTitle(fpsString);
			}
		}

		app.cleanup();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}