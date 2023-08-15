#include <objects/pyramid.h>
#include <glm/ext/matrix_transform.hpp>

Pyramid::Pyramid()
{
	createShaders();
}

void Pyramid::Init()
{
}

void Pyramid::Update(float deltaTime)
{
}

void Pyramid::Draw(const SceneParameters& sceneParams)
{
	Shader* lastBoundShader = nullptr;

	for (auto& model : _models)
	{
		auto* shader = model.GetShader();
		auto* mesh = model.GetMesh();

		if (shader != lastBoundShader)
		{
			shader->Bind();
			shader->SetMat4("projection", sceneParams.ProjectionMatrix);
			shader->SetMat4("view", sceneParams.ViewMatrix);

			// Set Camera Position
			shader->SetVec3("eyePos", sceneParams.CameraPosition);

			//handle lights
			for (auto i = 0; i < MAX_POINT_LIGHTS; i++)
			{
				std::string baseUniformName = "pointLights[";
				baseUniformName += std::to_string(i) + "]";

				PointLightStruct pointLight = i < sceneParams.Lights.size() ? sceneParams.Lights[i] : PointLightStruct{};

				shader->SetVec3(baseUniformName + ".Position", pointLight.Position);

				shader->SetVec3(baseUniformName + ".Diffuse", pointLight.DiffuseColor);
				shader->SetVec3(baseUniformName + ".Ambient", pointLight.AmbientColor);
				shader->SetVec3(baseUniformName + ".Specular", pointLight.SpecularColor);

				shader->SetFloat(baseUniformName + ".Constant", pointLight.Constant);
				shader->SetFloat(baseUniformName + ".Linear", pointLight.Linear);
				shader->SetFloat(baseUniformName + ".Quadratic", pointLight.Quadratic);
			}

			shader->SetVec3("dirLight.Direction", sceneParams.DirLight.Direction);
			shader->SetVec3("dirLight.Diffuse", sceneParams.DirLight.DiffuseColor);
			shader->SetVec3("dirLight.Ambient", sceneParams.DirLight.AmbientColor);
			shader->SetVec3("dirLight.Specular", sceneParams.DirLight.SpecularColor);

		}

		shader->SetMat4("model", Transform * mesh->Transform);

		mesh->Draw();
	}
}

void Pyramid::ProcessLighting(SceneParameters& sceneParams)
{
	// This isn't a light so do nothing
}

void Pyramid::createShaders()
{
	_basicLitShader = std::make_shared<Shader>(Path("assets/shaders/basic_lit.vert"), Path("assets/shaders/basic_lit.frag"));

	auto pyramid = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidElements, glm::vec3(1.f, 1.f, 1.f));

	_models.emplace_back(pyramid, _basicLitShader);
	pyramid->Transform = glm::rotate(pyramid->Transform, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));

}
