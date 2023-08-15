#pragma once

#include <objects/object.h>
#include <core/model.h>

class Pyramid : public Object
{
public:
	Pyramid();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw(const SceneParameters& sceneParams) override;
	void ProcessLighting(SceneParameters& sceneParams) override;

private:
	void createShaders();
	std::shared_ptr<Shader> _basicLitShader;
	std::shared_ptr<Shader> _textureShader;

	std::vector<Model> _models{};
};