#include <objects/blue_sphere.h>
#include <glm/ext/matrix_transform.hpp>

BlueSphere::BlueSphere()
{
	createShaders();
}

void BlueSphere::Init()
{
}

void BlueSphere::Update(float deltaTime)
{
}

void BlueSphere::Draw(const SceneParameters& sceneParams)
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

void BlueSphere::ProcessLighting(SceneParameters& sceneParams)
{
	// This isn't a light so do nothing
}

void BlueSphere::createShaders()
{
	float stackCount = 100.f;
	float sectorCount = 100.f;

	_basicLitShader = std::make_shared<Shader>(Path("assets/shaders/basic_lit.vert"), Path("assets/shaders/basic_lit.frag"));

	auto blueSphereTexture = std::make_shared<Texture>("assets/textures/bluespheretexture.jpg");
	_basicLitShader->AddTexture(blueSphereTexture);

	_sphereVertices = Shapes::GetSphereVertices(2.f, sectorCount, stackCount);
	_sphereElements = Shapes::GetSphereElements(stackCount, sectorCount);

	auto blueSphere = std::make_shared<Mesh>(_sphereVertices, _sphereElements, glm::vec3(1.f, 1.f, 1.f));
	_models.emplace_back(blueSphere, _basicLitShader);
	blueSphere->Transform = glm::translate(blueSphere->Transform, glm::vec3(2.f, 0.8f, -0.2f));
	blueSphere->Transform = glm::scale(blueSphere->Transform, glm::vec3(0.5f, 0.5f, 0.5f));
}
