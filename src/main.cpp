#include <iostream>

#include "GameEngine.h"

int main() {
	GameEngine engine;

	try {
		engine.init();

		engine.run();

		engine.cleanup();
		//std::cin.get();
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		std::cin.get();
		exit(1);
	}

	return 0;
}