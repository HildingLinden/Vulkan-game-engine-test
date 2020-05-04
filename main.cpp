#include "engine.h"
#include "shapes.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include <glm/gtc/matrix_transform.hpp>

class FPSCounter {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
	float fpsUpdateInterval;
	float fpsUpdateTimer = 0.0f;
	int frameCount = 0;
	std::string title;
	Engine &app;
public:
	FPSCounter(std::string title, Engine &app, float interval) : title(title), app(app), fpsUpdateInterval(interval) {}

	float getTime() {
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsedTime = currentTime - time;
		time = currentTime;

		fpsUpdateTimer += elapsedTime.count();
		frameCount++;

		if (fpsUpdateTimer > fpsUpdateInterval) {
			int fps = round(frameCount / fpsUpdateTimer);
			app.changeTitle(title + std::to_string(fps) + " fps - ");
			fpsUpdateTimer = 0.0f;
			frameCount = 0;
		}

		return elapsedTime.count();
	}
};

std::vector<Rect> rects;

const uint32_t WIDTH = 2300;
const uint32_t HEIGHT = 1300;

int main() {
	try {
		// Initialization
		std::string title("Vulkan Test Application - ");

		Engine app(WIDTH, HEIGHT, title, ShaderBufferType::SSBO);
		app.init();		

		FPSCounter fpsCounter(title, app, 1.0f);

		// Main game loop
		while (!app.shouldClose()) {
			float timeElapsed = fpsCounter.getTime();

			// User input
			app.pollEvents();			
			if (app.checkMouseClick()) {
				std::vector<Rect> tmpRects;
				for (size_t i = 0; i < 1000; i++) {
					Rect r(rand() % WIDTH, rand() % HEIGHT, 2, 2);
					tmpRects.push_back(r);
				}
				if (app.addRects(tmpRects)) {
					rects.insert(std::end(rects), std::begin(tmpRects), std::end(tmpRects));
				}
			}			

			// Physics
			#pragma omp parallel for 
			for (int i = 0; i < rects.size(); i++) {
				rects[i].applyForce(glm::vec2(0.0f, 500.0f));
				rects[i].update(timeElapsed, (float)WIDTH, (float)HEIGHT);
				app.updateMatrix(rects[i]);
			}

			// Render
			app.drawFrame();
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