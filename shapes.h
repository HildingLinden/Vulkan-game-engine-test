#pragma once
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Rect {
public:
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 *mvpMatrix = nullptr;

	Rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	void update(float timeElapsed);

	void applyForce(glm::vec2 force, float timeElapsed);

private:
	glm::vec2 vel = glm::vec2(0.0f);
	glm::vec2 acc = glm::vec2(0.0f);
};