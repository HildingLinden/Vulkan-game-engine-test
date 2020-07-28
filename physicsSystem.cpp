#include "physicsSystem.h"

#include <limits>
#include <algorithm>
#include <iostream>

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(float elapsedTime) {
	for (Rect &rect : *objects) {
		if (!rect.isStatic && !(rect.vel[0] == 0.0f && rect.vel[1] == 0.0f)) {
			// Gravity
			rect.vel[1] += 500 * elapsedTime;

			float velX = rect.vel[0] * elapsedTime;
			float velY = rect.vel[1] * elapsedTime;

			// Check if going to collide with any static rectangles
			for (Rect &testRect : *objects) {
				if (testRect.isStatic && &testRect != &rect) {
					float normalX, normalY;
					float collisionTime;

					if (sweptAABB(testRect, rect, velX, velY, normalX, normalY, collisionTime)) {
						if (abs(normalX) > 0.0f) {
							rect.x += velX * collisionTime;
							rect.y += velY * collisionTime;
							rect.vel[0] = 0.0f;
						}
						else {
							rect.x += velX * collisionTime;
							rect.y += velY * collisionTime;
							rect.vel[1] = 0.0f;
						}
					}
				}
			}

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

bool PhysicsSystem::sweptAABB(Rect &staticRect, Rect &currentRect, float velX, float velY, float &normalX, float &normalY, float &time) {
	// Get middle of current rectangle
	float currentX = currentRect.x + currentRect.width / 2;
	float currentY = currentRect.y + currentRect.height / 2;

	// Get expanded static rectangle
	float staticX = staticRect.x - currentRect.width / 2;
	float staticY = staticRect.y - currentRect.height / 2;

	// Get near and far intersects of both axes
	float nearX, farX;
	float nearY, farY;

	nearX = (staticX - currentX) / velX;
	nearY = (staticY - currentY) / velY;
	
	farX = (staticX + staticRect.width + currentRect.width - currentX) / velX;
	farY = (staticY + staticRect.height + currentRect.height - currentY) / velY;


	// Check if far is closer than near, in case the velocity is negative
	if (nearX > farX) std::swap(nearX, farX);
	if (nearY > farY) std::swap(nearY, farY);

	// If no collision
	if (nearX > farY || nearY > farX) return false;

	float nearHit = std::max(nearX, nearY);
	float farHit = std::min(farX, farY);

	// If collision is behind
	if (farHit < 0) return false;

	//float contactPoint = currentRect + 

	normalX = 0.0f;
	normalY = 0.0f;

	// Get normals
	if (nearX > nearY) {
		if (currentRect.vel[0] < 0) {
			normalX = 1.0f;			
		}
		else {
			normalX = -1.0f;
		}
	}
	else if (nearX < nearY) {
		if (currentRect.vel[1] < 0) {
			normalY = 1.0f;
		}
		else {
			normalY = -1.0f;
		}
	}

	if (nearHit > 1.0f) return false;
	
	time = nearHit;

	return true;	
}
