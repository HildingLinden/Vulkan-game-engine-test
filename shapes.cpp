#include "shapes.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Rect::Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {
	vel = glm::vec2(rand() % 201 - 100, 0.0f);
}

void Rect::update(float timeElapsed, float boundingX, float boundingY) {
	vel += acc * timeElapsed;
	x += vel[0] * timeElapsed;
	y += vel[1] * timeElapsed;

	// Right
	if (x + width > boundingX) {
		vel[0] *= -1.0f;
		x = boundingX - width;
	} // Left
	else if (x < 0) {
		vel[0] *= -1.0f;
		x = 0;
	}

	// Bottom
	if (y + height > boundingY) {
		vel[1] *= -1.0f;
		y = boundingY - height;
	}	

	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));

	acc[0] = 0.0f;
	acc[1] = 0.0f;
}

void Rect::applyForce(glm::vec2 force) {
	acc = force;
}
