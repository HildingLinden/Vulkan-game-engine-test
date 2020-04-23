#include "engine.h"
#include "shapes.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

int main() {
	Engine app(800, 600);
	
	Rect rect1(50, 50, 100, 100);
	app.rects.push_back(rect1);
	app.addVerticesAndIndices(rect1);

	Rect rect2(300, 300, 10, 10);
	app.rects.push_back(rect2);
	app.addVerticesAndIndices(rect2);

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}