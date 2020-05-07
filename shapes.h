#pragma once

#include <cstdint>
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Rect {
public:
	float x;
	float y;
	float width;
	float height;
	glm::mat4 *modelMatrix = nullptr;

	Rect(float x, float y, float width, float height);

	void update(float timeElapsed, float boundingX, float boundingY, std::vector<Rect> &rects);

	void applyForce(glm::vec2 force);

private:
	glm::vec2 vel = glm::vec2(0.0f);
	glm::vec2 acc = glm::vec2(0.0f);
};