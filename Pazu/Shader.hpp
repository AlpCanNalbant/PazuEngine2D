#pragma once
#include <unordered_map>
#include <string>
#include "GL/glew.h"
#include "mathfu/glsl_mappings.h"
#include "Resource.hpp"

namespace Pazu
{
	class Shader final : public Resource
	{
	public:
		Shader() = default;
		~Shader();
		Shader(const Shader &) = default;
		Shader(Shader &&) = default;
		Shader &operator=(const Shader &) = default;
		Shader &operator=(Shader &&) = default;
		void Use();
		void Unuse();
		GLboolean GetBool(GLint loc);
		GLint GetInt(GLint loc);
		GLfloat GetFloat(GLint loc);
		mathfu::vec2 GetVec2(GLint loc);
		mathfu::vec3 GetVec3(GLint loc);
		mathfu::vec4 GetVec4(GLint loc);
		mathfu::mat4 GetMat4(GLint loc);
		GLuint GetProgramID();
		void SetBool(GLint loc, GLboolean val);
		void SetInt(GLint loc, GLint val);
		void SetFloat(GLint loc, GLfloat val);
		void SetVec2(GLint loc, mathfu::vec2 val);
		void SetVec3(GLint loc, mathfu::vec3 val);
		void SetVec4(GLint loc, mathfu::vec4 val);
		void SetMat3(GLint loc, mathfu::mat3 val);
		void SetMat4(GLint loc, mathfu::mat4 val);
		void SetProgramID(GLuint programID);

		GLuint programID{0};
		std::unordered_map<std::string, GLint> uniforms;
	};
}
