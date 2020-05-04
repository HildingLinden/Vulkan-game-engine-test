#pragma once

#include <cstdint>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Rect {
public:
	float x;
	float y;
	float width;
	float height;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 *mvpMatrix = nullptr;

	Rect(float x, float y, float width, float height);

	void update(float timeElapsed, float boundingX, float boundingY);

	void applyForce(glm::vec2 force);

private:
	glm::vec2 vel = glm::vec2(0.0f);
	glm::vec2 acc = glm::vec2(0.0f);
};