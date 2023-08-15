#include <core/application.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <rendering/types.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <core/shapes.h>
#include <objects/cube.h>
#include <objects/point_light.h>
#include <objects/pyramid.h>
#include <objects/table.h>
#include <objects/pen.h>
#include <objects/blue_sphere.h>
#include <objects/multi_sphere.h>

Application::Application(std::string WindowTitle, int width, int height) 
	: _applicationName{WindowTitle}, _width{width}, _height{height},
	_camera { width, height, {0.f, 2.f, 5.f}, true},
	_cameraLookSpeed {0.1f, 0.1f}
{}

void Application::Run()
{
	// Open window
	if (!openWindow())
	{
		return;
	};

	setupInputs();

	_running = true;

	// Set up the scene
	setUpScene();

	// Run application
	while (_running)
	{
		float currentTime = glfwGetTime();

		if (_lastFrameTime == -1.f)
		{
			_lastFrameTime = currentTime;
		}

		auto deltaTime = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		if (glfwWindowShouldClose(_window))
		{
			_running = false;
			continue;
		}

		// Update
		update(deltaTime);

		// Draw
		draw();
	}

	glfwTerminate();
}

bool Application::openWindow()
{
	glfwInit(); // Initializes window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);

	if (!_window)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, (void*)this);
	// Look for Window resize
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);

		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_width = width;
		app->_height = height;

		app->_camera.SetSize(width, height);
		});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		glfwTerminate();

		return false;
	}

	// Enable vsync
	glfwSwapInterval(1);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Cull back faces
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	return true; 
}

void Application::setupInputs()
{

	// TODO: Create as its own function for key call backs like mousePositionCallback
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		
		switch (key) 
		{
			case GLFW_KEY_ESCAPE:
			{
				if (action == GLFW_PRESS)
				{
					app->_running = false;
				}
				break;
			}
			case GLFW_KEY_F11: 
			{
				if (action == GLFW_PRESS)
				{
					app->_camera.SetIsPerspective(!app->_camera.IsPerspective());
				}
			}
			default: {}
		}
		});

	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		});

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_camera.IncrementZoom(yOffset * 2);
		
		});

	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT: 
			{
				if (action == GLFW_PRESS)
				{
					std::cout << "Mouse button left pressed" << std::endl;
				}
				else
				{
					std::cout << "Mouse button left released" << std::endl;
				}
				break;
			}
			case GLFW_MOUSE_BUTTON_MIDDLE:
			{
				if (action == GLFW_PRESS)
				{
					std::cout << "Mouse button middle pressed" << std::endl;
				}
				else
				{
					std::cout << "Mouse button middle released" << std::endl;
				}
				break;
			}
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				if (action == GLFW_PRESS)
				{
					std::cout << "Mouse button right pressed" << std::endl;
				}
				else
				{
					std::cout << "Mouse button right released" << std::endl;
				}
				break;
			}
			default:
			{
				std::cout << "Unhandled mouse button event" << std::endl;
				break;
			}

		}
		});
}

void Application::setUpScene()
{
	_objects.push_back(std::make_unique<Table>());
	_objects.push_back(std::make_unique<Pen>());
	_objects.push_back(std::make_unique<Cube>());
	_objects.push_back(std::make_unique<MultiSphere>());
	_objects.push_back(std::make_unique<BlueSphere>());
	auto &light = _objects.emplace_back(std::make_unique<PointLight>());
	light->Transform = glm::translate(light->Transform, glm::vec3(0.f, 10.f, 2.f));

	auto* castLight = reinterpret_cast<PointLight*>(light.get());
	castLight->AmbientColor = { 1.f, 1.f, 1.f };
	castLight->DiffuseColor = { 1.f, 1.f, 1.f };
	castLight->SpecularColor = { 1.f, 1.f, 1.f };

	castLight->Constant = 1.f;
	castLight->Linear = 0.045f;
	castLight->Quadratic = 0.0075f;
}

void Application::update(float deltaTime)
{
	glfwPollEvents(); // Looks for any changes in the window

	handleInput(deltaTime);

	for (auto& object : _objects)
	{
		object->Update(deltaTime);
	}
}



bool Application::draw()
{
	// Change Window Color
	glClearColor(0.56f, 0.8f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera

	// View Maatrix
	glm::mat4 view = _camera.GetViewMatrix();
	// Projection Matrix
	glm::mat4 projection = _camera.GetProjectionMatrix();

	SceneParameters sceneParams{
	.ProjectionMatrix = projection,
	.ViewMatrix = view,
	.CameraPosition = _camera.GetPosition(),
	.DirLight = {
		.Direction = glm::normalize(glm::vec3{ 0.f, 10.f, 0.25f }),
		.AmbientColor = {1.f, 1.f, 1.f},
		.DiffuseColor = {1.f, 1.f, 1.f},
		.SpecularColor = {0.f, 0.f, 0.f}
	}
	};
	
	for (auto& model : _objects)
	{
		model->ProcessLighting(sceneParams);
	}

	for (auto& model : _objects)
	{
		model->Draw(sceneParams);
	}

	glfwSwapBuffers(_window);

	return false;
}

void Application::handleInput(float deltaTime)
{
	auto moveAmount = _moveSpeed * deltaTime;

	if (glfwGetKey(_window, GLFW_KEY_W))
	{
		_camera.MoveCamera(Camera::MoveDirection::Forward, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_S))
	{
		_camera.MoveCamera(Camera::MoveDirection::Backward, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_A))
	{
		_camera.MoveCamera(Camera::MoveDirection::Left, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_D))
	{
		_camera.MoveCamera(Camera::MoveDirection::Right, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_Q))
	{
		_camera.MoveCamera(Camera::MoveDirection::Up, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_E))
	{
		_camera.MoveCamera(Camera::MoveDirection::Down, moveAmount);
	}

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	mousePositionCallback(xpos, ypos);
}

void Application::mousePositionCallback(double xpos, double ypos)
{
	if (!_firstMouse)
	{
		_lastMousePosition.x = static_cast<float>(xpos);
		_lastMousePosition.y = static_cast<float>(ypos);
		_firstMouse = true;
	}

	glm::vec2 moveAmount
	{
		xpos - _lastMousePosition.x,
		_lastMousePosition.y - ypos
	};

	_lastMousePosition.x = static_cast<float>(xpos);
	_lastMousePosition.y = static_cast<float>(ypos);

	_camera.RotateBy(moveAmount.x * _cameraLookSpeed.x, moveAmount.y * _cameraLookSpeed.y);
}
