#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 Position { 0.f, 0.f, 0.f };
	glm::vec3 Color { 1.f, 1.f, 1.f };
	glm::vec3 Normal { 0.f, 0.f, 0.f };
	glm::vec2 Uv { 1.f, 1.f };
};

struct SceneParameters
{
	glm::mat4 ProjetionMatrix { 1.f };
	glm::mat4 ViewMatrix { 1.f };

	uint32_t LightsInScene { 0 };
	glm::vec3 LightPos0 {};
};