#include <objects/point_light.h>
#include <core/shapes.h>
#include <glm/ext/matrix_transform.hpp>

PointLight::PointLight()
{
	createShader();
	createMesh();
}

void PointLight::Init()
{
}

void PointLight::Update(float deltaTime)
{
}

void PointLight::Draw(const SceneParameters& sceneParams)
{
	for (auto& model : _models)
	{
		auto* shader = model.GetShader();
		auto* mesh = model.GetMesh();
		shader->Bind();
		shader->SetMat4("projection", sceneParams.ProjectionMatrix);
		shader->SetMat4("view", sceneParams.ViewMatrix);
		shader->SetMat4("model", Transform * mesh->Transform);

		mesh->Draw();
	}
}

void PointLight::ProcessLighting(SceneParameters& sceneParams)
{
	if (sceneParams.Lights.size() < MAX_POINT_LIGHTS)
	{
		PointLightStruct pointLight
		{
			.Position = glm::vec3(Transform[3]),
			.AmbientColor = AmbientColor,
			.DiffuseColor = DiffuseColor, 
			.SpecularColor = SpecularColor,
			.Constant = Constant,
			.Linear = Linear,
			.Quadratic = Quadratic
		};

		sceneParams.Lights.emplace_back(pointLight);
	}
}

void PointLight::createShader()
{
	_basicUnlitShader = std::make_shared<Shader>(Path("assets/shaders/basic_unlit_color.vert"), Path("assets/shaders/basic_unlit_color.frag"));
}

void PointLight::createMesh()
{
}
