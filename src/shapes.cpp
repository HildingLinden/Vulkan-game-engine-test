#include "shapes.h"
#include <glm/gtx/transform.hpp>

#include <iostream>

Rect::Rect(float x, float y, float width, float height, std::string texture, bool isStatic) : x(x), y(y), width(width), height(height), texture(texture), isStatic(isStatic) {
	vel = glm::vec2(rand() % 201 - 100, 0.0f);
}

void Rect::update() {
	*modelMatrix = glm::translate(glm::vec3(x, y, 0.0f));
}