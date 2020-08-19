#include "graphicsEngine.h"
#include "shapes.h"
#include "physicsSystem.h"
#include "gameObjects.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

#include <glm/gtc/matrix_transform.hpp>

class FPSCounter {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
	float fpsUpdateInterval;
	float fpsUpdateTimer = 0.0f;
	int frameCount = 0;
	std::string title;
	GraphicsEngine *app;
public:
	FPSCounter(std::string title, GraphicsEngine *app, float interval) : title(title), app(app), fpsUpdateInterval(interval) {}

	float getTime() {
		std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsedTime = currentTime - time;
		time = currentTime;

		fpsUpdateTimer += elapsedTime.count();
		frameCount++;

		if (fpsUpdateTimer > fpsUpdateInterval) {
			int fps = (int)round(frameCount / fpsUpdateTimer);
			app->changeTitle(title + std::to_string(fps) + " fps - ");
			fpsUpdateTimer = 0.0f;
			frameCount = 0;
		}
		 
		return elapsedTime.count();
	}
};

std::vector<Rect> rects;

uint32_t WIDTH = 1920;
uint32_t HEIGHT = 1080;

const bool LIMIT_FPS = false;

int main() {

	try {
		// Initialization
		std::string title("Vulkan Test Application - ");

		GraphicsEngine app(WIDTH, HEIGHT, title);
		app.init();		

		GameObjects gameObjects(&app);

		FPSCounter fpsCounter(title, &app, 1.0f);

		PhysicsSystem physics(&gameObjects.rects);

		// Seeding the RNG
		srand((unsigned)time(NULL));

		// Creating some static rectangles
		size_t nrPlatforms = 5;
		size_t platformWidth = 10;
		size_t rectSize = 20;

		for (size_t i = 0; i < nrPlatforms; i++) {
			for (size_t j = 0; j < platformWidth; j++) {
				gameObjects.addRect(
					200 + i * (platformWidth * rectSize + 30) + j * rectSize,
					200 + i * (rectSize + 20),
					rectSize,
					rectSize,
					"textures/ground.png"
				);
			}
		}

		for (size_t i = 0; i < 500; i++) {
			gameObjects.addRect(100 + i * 2, 600, 30, 30, "textures/ground.png");
		}

		gameObjects.addRect(100, 10, 50, 75, "textures/player_right.png", false);

		// Main game loop
		while (!app.shouldClose()) {
			float elapsedTime = fpsCounter.getTime();

			// Limit fps
			if (LIMIT_FPS && elapsedTime < 0.01) {
				std::this_thread::sleep_for(std::chrono::microseconds(10000 - (long)(elapsedTime * 1000000)));
				elapsedTime += fpsCounter.getTime();
			}

			uint32_t currentWidth = app.getWidth();
			uint32_t currentHeight = app.getHeight();

			physics.setScreenBB(currentWidth, currentHeight);

			// User input
			app.pollEvents();
			if (app.checkKeyPress(GLFW_KEY_RIGHT)) {
				for (Rect& rect : gameObjects.rects) {
					rect.vel[0] += 500 * elapsedTime;
					rect.vel[0] = std::min(200.0f, rect.vel[0]);			
				}
			}
			if (app.checkKeyPress(GLFW_KEY_LEFT)) {
				for (Rect& rect : gameObjects.rects) {
					rect.vel[0] -= 500 * elapsedTime;
					rect.vel[0] = std::max(-200.0f, rect.vel[0]);
				}
			}
			if (app.checkKeyPress(GLFW_KEY_UP)) {
				for (Rect& rect : gameObjects.rects) {
					if (rect.canJump) {
						rect.vel[1] -= 500;
						rect.canJump = false;
					}
				}
			}
			if (app.checkMouseClick()) {
				for (size_t i = 0; i < 1000; i++) {
					gameObjects.addRect(rand() % (WIDTH - 100), rand() & (HEIGHT - 100), 100, 100, "textures/ground.png");
				}
			}

			
			gameObjects.checkNewRects();

			if (gameObjects.rects.size() > 0) {
				// Physics
				physics.update(elapsedTime);

				// Render
				app.drawFrame();
			}
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