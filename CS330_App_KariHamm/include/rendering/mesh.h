#pragma once
#include <vector>
#include <core/shapes.h>
#include <glad/glad.h>

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements, const glm::vec3& color);

	void Draw();

	glm::mat4 Transform{ 1.f };

private:
	void init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

private:
	uint32_t _elementCount{ 0 };

	GLuint _vertexBufferObject{}; // VBO
	GLuint _shaderProgram{};
	GLuint _vertexArrayObject{}; // VAO
	GLuint _elementBufferObject{}; // EBO
};