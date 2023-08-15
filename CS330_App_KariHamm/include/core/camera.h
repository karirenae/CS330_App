#pragma once
#include <glm/glm.hpp>

class Camera {
public:
	enum class MoveDirection
	{
		Forward,
		Backward,
		Left,
		Right,
		Up,
		Down
	};

	explicit Camera(int width, int height, glm::vec3 initialPosition = glm::vec3 {0.f, 0.f, -20.f}, bool isPerspective = true);
	// Perspective = vanishing point
	// Orthographic = same size lines no matter the camera distance

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition() const { return _position; }

	bool IsPerspective() const { return _isPerspective; }
	void SetIsPerspective(bool isPerspective) { _isPerspective = isPerspective; }
	void SetSize(int width, int height)
	{
		_width = width;
		_height = height;
	}

	void MoveCamera(MoveDirection direction, float moveAmount);
	void RotateBy(float yaw, float pitch);
	void IncrementZoom(float amount);
private:
	void recalculateVectors();

private:
	bool _isPerspective {true}; 	// Perspective = vanishing point; Orthographic = same size lines no matter the camera distance
	
	glm::vec3 _position {}; // 0 on x axis, 0 on y axis, -5 on z access so we are stepped back from the scene. This is where the camera sits
	glm::vec3 _lookDirection {}; // We want to look at the center point so this is 0, 0, 0, where the camera is pointed at
	glm::vec3 _upDirection { 0.f, 1.f, 0.f }; // This is sking which direction is up. Having the y axis set to 1 means we want the y axis to be our "up"

	float _yaw { - 90.f };
	float _pitch {};

	float _fieldOfView { 75.f }; // Field of view in radians
	int _width { 0 };
	int _height { 0 };
	float _nearClip { 0.1f }; // How close until you stop rendering
	float _farClip { 100.f }; // How far away until you stop rendering
};