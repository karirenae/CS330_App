#pragma once

#include <objects/object.h>
#include <core/model.h>

class BlueSphere : public Object
{
public:
	BlueSphere();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw(const SceneParameters& sceneParams) override;
	void ProcessLighting(SceneParameters& sceneParams) override;

private:
	void createShaders();
	std::shared_ptr<Shader> _basicLitShader;
	std::shared_ptr<Shader> _textureShader;

	std::vector<Model> _models{};
	std::vector<Vertex> _sphereVertices{};
	std::vector<uint32_t> _sphereElements;
};