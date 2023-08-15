#pragma once

#include <rendering/mesh.h>
#include <rendering/shader.h>

class Model
{
public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
	Shader* GetShader() { return _shader.get(); }
	Mesh* GetMesh() { return _mesh.get(); }

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Mesh> _mesh;
};