#include "physicsSystem.h"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(float elapsedTime) {
	for (Rect &rect : *objects) {
		if (!rect.isStatic) {
			// Gravity
			rect.vel[1] += 500 * elapsedTime;

			// Set new position according to velocity and time since last frame
			rect.x += rect.vel[0] * elapsedTime;
			rect.y += rect.vel[1] * elapsedTime;

			// Static Collision Detection (Screen)
			// Right
			if (rect.x + rect.width > boundingX) {
				rect.vel[0] *= -1.0f;
				rect.x = boundingX - rect.width;
			} // Left
			else if (rect.x < 0) {
				rect.vel[0] *= -1.0f;
				rect.x = 0;
			}

			// Bottom
			if (rect.y + rect.height > boundingY) {
				rect.vel[1] *= -1.0f;
				rect.y = boundingY - rect.height;
			}

			sweptAABB(rect);
		}
		rect.update();
	}
}

void PhysicsSystem::updateObjects(std::vector<Rect> &newObjects) {
	objects = &newObjects;
}

void PhysicsSystem::setScreenBB(float width, float height) {
	boundingX = width;
	boundingY = height;
}

float PhysicsSystem::sweptAABB(Rect &currentRect) {
	for (Rect &rect : *objects) {
		if (rect.isStatic && &rect != &currentRect) {

		}
	}

	return 0.0f;
}
