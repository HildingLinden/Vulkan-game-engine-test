#include "physicsSystem.h"

#include <limits>
#include <algorithm>
#include <iostream>

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(float elapsedTime) {
	for (Rect &rect : *objects) {
		std::vector<std::pair<float, int>> collisions;

		if (!rect.isStatic) {
			// Gravity
			rect.vel[1] += 500 * elapsedTime;

			if (abs(rect.vel[0]) < 0.0001f && abs(rect.vel[1]) < 0.0001f) break;

			// Pre-compute modified velocity for collision detection
			float modifiedInverseVelocityX = 1 / (rect.vel[0] * elapsedTime);
			float modifiedInverseVelocityY = 1 / (rect.vel[1] * elapsedTime);

			// Get the distance to all collisions with each static object
			int index = 0;
			for (Rect &testRect : *objects) {
				if (testRect.isStatic && &testRect != &rect) {
					float normalX, normalY;
					float collisionTime;

					if (sweptAABB(testRect, rect, modifiedInverseVelocityX, modifiedInverseVelocityY, normalX, normalY, collisionTime)) {
						collisions.push_back({collisionTime, index});
					}
				}

				index++;
			}

			// Sort the collisions by distance
			std::sort(collisions.begin(), collisions.end());

			// Resolve the collisions in the right order
			for (std::pair<float, int> &pair: collisions) {
				Rect &testRect = objects->at(pair.second);

				if (testRect.isStatic && &testRect != &rect) {
					float normalX, normalY;
					float collisionTime;

					modifiedInverseVelocityX = 1 / (rect.vel[0] * elapsedTime);
					modifiedInverseVelocityY = 1 / (rect.vel[1] * elapsedTime);

					// If collision change velocity to reach the object but not further
					if (sweptAABB(testRect, rect, modifiedInverseVelocityX, modifiedInverseVelocityY, normalX, normalY, collisionTime)) {
						if (abs(normalX) > 0.0f) {
							rect.vel[0] -= rect.vel[0] * (1.0f - collisionTime);
						}
						else {
							if (normalY < 0) rect.canJump = true;
							rect.vel[1] -= rect.vel[1] * (1.0f - collisionTime);
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

	nearX = (staticX - currentX) * velX;
	nearY = (staticY - currentY) * velY;
	
	farX = (staticX + staticRect.width + currentRect.width - currentX) * velX;
	farY = (staticY + staticRect.height + currentRect.height - currentY) * velY;

	// Check if division by zero has occured
	if (std::isnan(nearX) || std::isnan(nearY)) return false;
	if (std::isnan(farX) || std::isnan(farY)) return false;

	// Check if far is closer than near, in case the velocity is negative
	if (nearX > farX) std::swap(nearX, farX);
	if (nearY > farY) std::swap(nearY, farY);

	// If no collision
	if (nearX > farY || nearY > farX) return false;
	if (nearX < 0.0f && nearY < 0.0f) return false;
	if (nearX > 1.0f || nearY > 1.0f) return false;

	float nearHit = std::max(nearX, nearY);
	float farHit = std::min(farX, farY);

	//float contactPointX = currentRect.x + nearHit / velX;
	//float contactPointY = currentRect.y + nearHit / velY;

	normalX = 0.0f;
	normalY = 0.0f;

	// Get normals
	if (nearX > nearY) {
		if (currentRect.vel[0] < 0.0f) {
			normalX = 1.0f;			
		}
		else {
			normalX = -1.0f;
		}
	}
	else if (nearX < nearY) {
		if (currentRect.vel[1] < 0.0f) {
			normalY = 1.0f;
		}
		else {
			normalY = -1.0f;
		}
	}
	
	time = nearHit;

	return true;	
}
