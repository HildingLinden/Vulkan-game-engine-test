#pragma once
#include <cstdint>
#include <glm/mat4x4.hpp>

class Rect {
public:
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 *mvpMatrix = nullptr;

	Rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height) : x(x), y(y), width(width), height(height) {}
};