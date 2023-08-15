#include <objects/multi_sphere.h>
#include <glm/ext/matrix_transform.hpp>

MultiSphere::MultiSphere()
{
	createShaders();
}

void MultiSphere::Init()
{
}

void MultiSphere::Update(float deltaTime)
{
}

void MultiSphere::Draw(const SceneParameters& sceneParams)
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

void MultiSphere::ProcessLighting(SceneParameters& sceneParams)
{
	// This isn't a light so do nothing
}

void MultiSphere::createShaders()
{
	float stackCount = 100.f;
	float sectorCount = 100.f;

	_basicLitShader = std::make_shared<Shader>(Path("assets/shaders/basic_lit.vert"), Path("assets/shaders/basic_lit.frag"));

	auto multiSphereTexture = std::make_shared<Texture>("assets/textures/multispheretexture.jpg");
	_basicLitShader->AddTexture(multiSphereTexture);

	_sphereVertices = Shapes::GetSphereVertices(2.f, sectorCount, stackCount);
	_sphereElements = Shapes::GetSphereElements(stackCount, sectorCount);

	auto multiSphere = std::make_shared<Mesh>(_sphereVertices, _sphereElements);
	_models.emplace_back(multiSphere, _basicLitShader);
	multiSphere->Transform = glm::translate(multiSphere->Transform, glm::vec3(0.f, 0.8f, 0.f));
	multiSphere->Transform = glm::scale(multiSphere->Transform, glm::vec3(0.4f, 0.4f, 0.4f));
}
