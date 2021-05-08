#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vShader, const std::string& fShader);
	~Shader();

	void use();

	void setMat4(const std::string& name, const glm::mat4& mat);
	void setVec3f(const std::string& name, const glm::vec3& vec);
	void setVec4f(const std::string& name, const glm::vec4& vec);
	void set1i(const std::string& name, const GLint val);

private:

	void checkCompileErrors(unsigned int shader, std::string type);

	GLuint getLoc(const std::string& name);

	GLuint mId;

	std::unordered_map<std::string, GLuint> mUniformMap;
};

