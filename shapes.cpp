#include "shapes.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Rect::Rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) : x(x), y(y), width(width), height(height) {}

void Rect::update(float timeElapsed) {
	vel += acc * timeElapsed;
	glm::vec3 translation = glm::vec3(vel * timeElapsed, 0.0f);
	modelMatrix = glm::translate(modelMatrix, translation);
	acc = glm::vec2(0.0f, 0.0f);
}

void Rect::applyForce(glm::vec2 force, float timeElapsed) {
	acc += force * timeElapsed;
}
