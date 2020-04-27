#include "engine.h"
#include "shapes.h"

#include <iostream>
#include <string>
#include <cstdlib>

class FPSCounter {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
	float fpsUpdateInterval;
	float fpsUpdateTimer = 0.0f;
	int frameCount = 0;
	std::string title;
	Engine app;
public:
	FPSCounter(std::string title, Engine &app, float interval) : title(title), app(app), fpsUpdateInterval(interval) {}

	void start() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	float end() {
		endTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsedTime = endTime - startTime;

		fpsUpdateTimer += elapsedTime.count();
		frameCount++;

		if (fpsUpdateTimer > fpsUpdateInterval) {
			int fps = round(frameCount / fpsUpdateTimer);
			app.changeTitle(title + std::to_string(fps) + " fps");
			fpsUpdateTimer = 0.0f;
			frameCount = 0;
		}

		return elapsedTime.count();
	}
};

int main() {
	try {
		// Initialization
		std::string title("Vulkan Test Application - ");

		Engine app(1280, 720, title, ShaderBufferTypes::SSBO);
		app.init();		

		FPSCounter fpsCounter(title, app, 1.0f);

		// Main game loop
		while (!app.shouldClose()) {
			fpsCounter.start();

			// User input
			app.pollEvents();			
			if (app.checkMouseClick()) {
				std::vector<Rect> rects;
				for (size_t i = 0; i < 10; i++) {
					Rect r(rand() % 1280, rand() % 720, 10, 10);
					rects.push_back(r);
				}
				app.addRects(rects);
			}			

			// Render
			app.drawFrame();

			fpsCounter.end();
		}

		// Clean up
		app.cleanup();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}