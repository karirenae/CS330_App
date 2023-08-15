#include <rendering/shader.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	load(vertexSource, fragmentSource);
}

Shader::Shader(const Path& vertexPath, const Path& fragmentPath)
{
	try {
		// load sources from file
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		// load our shader
		load(vShaderStream.str(), fShaderStream.str());
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
}

void Shader::Bind()
{
	glUseProgram(_shaderProgram);

	SetInt("tex0", 0);

	for (auto i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		_textures[i]->Bind();
	}
}

void Shader::SetVec3(const std::string& uniformName, const glm::vec3& vec3) const
{
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1)
	{
		glUniform3fv(uniformLoc, 1, glm::value_ptr(vec3));
	}
	else
	{
		std::cerr << "ERROR::SHADER::VERTEX::SetVec3::FAILED" << uniformName << std::endl;
	}
}

void Shader::SetMat4(const std::string& uniformName, const glm::mat4& mat4) const
{
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1)
	{
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
	else
	{
		std::cerr << "ERROR::SHADER::VERTEX::SetMat4::FAILED" << uniformName << std::endl;
	}
}

void Shader::SetInt(const std::string& uniformName, int value) const
{
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1)
	{
		glUniform1i(uniformLoc, value);
	}
	else
	{
		std::cerr << "ERROR::SHADER::VERTEX::SetInt::FAILED" << uniformName << std::endl;
	}
}

void Shader::SetFloat(const std::string& uniformName, float value) const
{
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1)
	{
		glUniform1f(uniformLoc, value);
	}
	else
	{
		std::cerr << "ERROR::SHADER::VERTEX::SetFloat::FAILED" << uniformName << std::endl;
	}
}

void Shader::AddTexture(const std::shared_ptr<Texture>& texture)
{
	_textures.emplace_back(texture);
}

void Shader::load(const std::string& vertexSource, const std::string& fragmentSource)
{
	// VERTEX SHADER
	const char* vShaderCode = vertexSource.c_str();
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION::FAILED" << infoLog << std::endl;
	}

	// FRAGMENT SHADER
	const char* fShaderCode = fragmentSource.c_str();
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED" << infoLog << std::endl;
	}

	// Shader Program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	glGetShaderiv(_shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::LINK_STATUS::FAILURE" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(const std::string& uniformName) const
{
	return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}
