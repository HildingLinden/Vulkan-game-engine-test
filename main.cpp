#include "engine.h"
#include "shapes.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

int main() {
	Engine app(800, 600);
	
	Rect rect1(50, 50, 100, 100);
	app.rects.push_back(rect1);
	app.addVerticesAndIndices(rect1);

	//ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.0000001f, 10000000.0f);
	//ubo.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ubo.proj[1][1] *= -1; // Flip Y since OpenGL is flipped, also change winding order to counter_clockwise

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}