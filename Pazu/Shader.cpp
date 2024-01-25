#include "Shader.hpp"

namespace Pazu
{
	Shader::~Shader()
	{
		Use();
		glDeleteProgram(programID);
		Unuse();
	}

	void Shader::Use()
	{
		glUseProgram(programID);
	}

	void Shader::Unuse()
	{
		glUseProgram(0);
	}

	GLboolean Shader::GetBool(GLint loc)
	{
		GLint res;
		glGetUniformiv(programID, loc, &res);
		return res;
	}

	GLint Shader::GetInt(GLint loc)
	{
		GLint res;
		glGetUniformiv(programID, loc, &res);
		return res;
	}

	GLfloat Shader::GetFloat(GLint loc)
	{
		GLfloat res;
		glGetUniformfv(programID, loc, &res);
		return res;
	}

	mathfu::vec2 Shader::GetVec2(GLint loc)
	{
		mathfu::vec2 res;
		glGetUniformfv(programID, loc, &res[0]);
		return res;
	}

	mathfu::vec3 Shader::GetVec3(GLint loc)
	{
		mathfu::vec3 res;
		glGetUniformfv(programID, loc, &res[0]);
		return res;
	}

	mathfu::vec4 Shader::GetVec4(GLint loc)
	{
		mathfu::vec4 res;
		glGetUniformfv(programID, loc, &res[0]);
		return res;
	}

	mathfu::mat4 Shader::GetMat4(GLint loc)
	{
		mathfu::mat4 res;
		glGetUniformfv(programID, loc, &res[0]);
		return res;
	}

	GLuint Shader::GetProgramID()
	{
		return programID;
	}

	void Shader::SetBool(GLint loc, GLboolean val)
	{
		glUniform1i(loc, (GLint)val);
	}

	void Shader::SetInt(GLint loc, GLint val)
	{
		glUniform1i(loc, val);
	}

	void Shader::SetFloat(GLint loc, GLfloat val)
	{
		glUniform1f(loc, val);
	}

	void Shader::SetVec2(GLint loc, mathfu::vec2 val)
	{
		glUniform2f(loc, val.x, val.y);
	}

	void Shader::SetVec3(GLint loc, mathfu::vec3 val)
	{
		glUniform3f(loc, val.x, val.y, val.z);
	}

	void Shader::SetVec4(GLint loc, mathfu::vec4 val)
	{
		glUniform4f(loc, val.x, val.y, val.z, val.w);
	}

	void Shader::SetMat3(GLint loc, mathfu::mat3 val)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, &val[0]);
	}

	void Shader::SetMat4(GLint loc, mathfu::mat4 val)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0]);
	}

	void Shader::SetProgramID(GLuint programID)
	{
		this->programID = programID;
	}
}
