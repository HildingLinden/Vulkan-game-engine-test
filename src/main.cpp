#include <iostream>

#include "GameEngine.h"

int main() {
	GameEngine engine;

	try {
		engine.init();

		engine.run();

		engine.cleanup();
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	return 0;
}