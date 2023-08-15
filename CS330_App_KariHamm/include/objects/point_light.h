#pragma once

#include <objects/object.h>
#include <glad/glad.h>
#include <rendering/shader.h>
#include <rendering/mesh.h>
#include <core/model.h>

class PointLight : public Object
{
public:
	PointLight();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw(const SceneParameters& sceneParams) override;
	void ProcessLighting(SceneParameters& sceneParams) override;

public:
	glm::vec3 AmbientColor{};
	glm::vec3 DiffuseColor{};
	glm::vec3 SpecularColor{};

	float Constant{ 0.f };
	float Linear{ 0.f };
	float Quadratic{ 0.f };

private:
	void createShader();
	void createMesh();

private:
	std::shared_ptr<Shader> _basicUnlitShader{};
	std::shared_ptr<Mesh> _lightMesh{};

	std::vector<Model> _models{};

	float totalTime{ 0.f };
};