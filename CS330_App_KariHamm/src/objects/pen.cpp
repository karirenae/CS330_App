#include <objects/pen.h>
#include <glm/ext/matrix_transform.hpp>

Pen::Pen()
{
	createShaders();
}

void Pen::Init()
{
}

void Pen::Update(float deltaTime)
{
}

void Pen::Draw(const SceneParameters& sceneParams)
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

void Pen::ProcessLighting(SceneParameters& sceneParams)
{
	// This isn't a light so do nothing
}

void Pen::createShaders()
{
	_basicLitShader = std::make_shared<Shader>(Path("assets/shaders/basic_lit.vert"), Path("assets/shaders/basic_lit.frag"));

	auto penTexture = std::make_shared<Texture>("assets/textures/pentexture.jpg");
	_basicLitShader->AddTexture(penTexture);

	// 3D Pen
	//pyramid
	auto pyramidPen = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidElements, glm::vec3(1.f, 1.f, 1.f));
	
	_models.emplace_back(pyramidPen, _basicLitShader);

	pyramidPen->Transform = glm::translate(pyramidPen->Transform, glm::vec3(-3.f, 0.5f, 0.f));
	pyramidPen->Transform = glm::rotate(pyramidPen->Transform, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
	pyramidPen->Transform = glm::rotate(pyramidPen->Transform, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
	pyramidPen->Transform = glm::scale(pyramidPen->Transform, glm::vec3(0.5f, 0.5f, 0.5f));


	// cube
	auto cubePen = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements, glm::vec3(1.f, 1.f, 1.f));

	_models.emplace_back(cubePen, _basicLitShader);

	cubePen->Transform = glm::translate(cubePen->Transform, glm::vec3(-4.f, 0.5f, 0.f));
	cubePen->Transform = glm::scale(cubePen->Transform, glm::vec3(1.5f, 0.5f, 0.5f));

}
