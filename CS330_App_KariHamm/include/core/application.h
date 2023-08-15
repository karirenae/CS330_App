#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <rendering/mesh.h>
#include <rendering/shader.h>
#include <core/camera.h>
#include <objects/object.h>
#include <rendering/texture.h>

class Application
{
public:
	Application(std::string WindowTitle, int width, int height);
	
	void Run();

private:
	 bool openWindow();
	 void setupInputs();

	 void setUpScene();
	 void update(float deltaTime);
	 bool draw();

	 void handleInput(float deltaTime);
	 void mousePositionCallback(double xpos, double ypos);

private:
	std::string _applicationName {};
	int _width {};
	int _height {};
	GLFWwindow* _window{ nullptr };

	float _moveSpeed { 5.f };
	Camera _camera;
	std::vector<std::unique_ptr<Object>> _objects{};
	std::vector<Texture> _textures;
	std::vector<Mesh> _meshes;
	Shader _shader;

	bool _running { false };

	bool _firstMouse { false };
	glm::vec2 _lastMousePosition{};
	glm::vec2 _cameraLookSpeed{};

	float _lastFrameTime { -1.f };

	// Lighting variables
	float _ambientStrength{ 0.1f };
	glm::vec3 _ambientLightColor{ 1.f, 1.f, 1.f };
};