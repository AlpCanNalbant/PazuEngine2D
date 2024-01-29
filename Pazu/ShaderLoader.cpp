// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <fstream>
#include <sstream>
#include <iostream>
#include "Pazu/Resource.hpp"
#include "ShaderLoader.hpp"
#include "ResourceManager.hpp"

namespace Pazu
{
	std::shared_ptr<Resource> ShaderLoader::LoadResource(const std::string &resourcePath)
	{
		std::cout << "New shader is loading... Shader: " + resourcePath + '\n';
		Wcm::Log->Info("New shader is loading...").Sub("Shader", resourcePath);

		const auto shader = std::make_shared<Shader>();
		if (!LoadShader(*shader, resourcePath))
		{
			return nullptr;
		}

		GetActiveUniforms(*shader);
		manager->CacheResource<Shader>(resourcePath, shader);
		return shader;
	}

	bool ShaderLoader::LoadShader(Shader& shader, const std::string &path) const
	{
		const auto res = GetResource(manager->GetBasePath(true) + path);
		if (!res)
		{
			std::cerr << "Shader is cannot loaded from in the memory trying to load from in the disk...\n";
			Wcm::Log->Info("Shader is cannot loaded from in the memory trying to load from in the disk...");
			// If we cannot load the shader file from in the memory then try to load from in the disk.
			std::ifstream infile(manager->GetBasePath() + path);
			if (!infile.is_open())
			{
				std::cerr << "Shader file does not exist at '" + path + "'.\n";
				Wcm::Log->Error("Shader file does not exist.").Sub("Shader", manager->GetBasePath() + path);
				return false;
			}
			return CreateShader(shader, std::move(infile));
		}
		return CreateShader(shader, std::istringstream{reinterpret_cast<const char *>(res.value().data())});
	}

	bool ShaderLoader::CreateShader(Shader& shader, std::istream &&stream) const
	{
		shader.programID = glCreateProgram();
		GLuint vertShaderID, fragShaderID;
		std::string currentLine, vertShaderCode, fragShaderCode;
		bool isFragTitleFound, isVertTitleFound, isEndOfFile;
		while (isEndOfFile)
		{
			if (vertShaderCode.empty() && (isVertTitleFound = currentLine.find(vertShaderTitle) != std::string::npos))
			{
				FillVertexShaderCode(stream, currentLine, vertShaderCode);
				continue;
			}
			if (fragShaderCode.empty() && (isFragTitleFound = currentLine.find(fragShaderTitle) != std::string::npos))
			{
				FillFragmentShaderCode(stream, currentLine, fragShaderCode);
				continue;
			}
			isEndOfFile = static_cast<bool>(std::getline(stream, currentLine));
		}

		CompileShader(shader, vertShaderCode.c_str(), GL_VERTEX_SHADER, vertShaderID);
		CompileShader(shader, fragShaderCode.c_str(), GL_FRAGMENT_SHADER, fragShaderID);
		Link(shader, vertShaderID, fragShaderID);
		return true;
	}

	void ShaderLoader::CompileShader(Shader& shader, const GLchar* code, GLenum shaderType, GLuint& shaderID) const
	{
		GLint compiled;
		char infoLog[1024];

		shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
		glAttachShader(shader.programID, shaderID);

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::wcerr << "Fragment shader compilation error.\n" << infoLog << std::endl;
			Wcm::Log->Error("Fragment shader compilation error.").Sub("GLError", infoLog);
		}
	}

	void ShaderLoader::Link(Shader& shader, GLuint& vertShaderID, GLuint& fragShaderID) const
	{
		GLint linked;
		char infoLog[1024];

		glLinkProgram(shader.programID);

		glGetProgramiv(shader.programID, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			glGetProgramInfoLog(shader.programID, 1024, nullptr, infoLog);
			std::cerr << "Program linking error.\n" << infoLog << std::endl;
			Wcm::Log->Error("Program linking error.").Sub("GLError", infoLog);
		}

		glDetachShader(shader.programID, vertShaderID);
		glDetachShader(shader.programID, fragShaderID);
		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);
	}

	void ShaderLoader::GetActiveUniforms(Shader& shader) const
	{
		GLint uniformCount;
		glGetProgramiv(shader.programID, GL_ACTIVE_UNIFORMS, &uniformCount);

		GLsizei lenght;
		GLint size;
		GLenum type;
		const GLsizei bufSize = 16;
		GLchar name[bufSize];

		for (GLint i = 0; i < uniformCount; i++)
		{
			glGetActiveUniform(shader.programID, (GLuint)i, bufSize, &lenght, &size, &type, name);

			shader.uniforms.insert(std::make_pair(name, glGetUniformLocation(shader.programID, name)));
		}
	}

	void ShaderLoader::FillVertexShaderCode(std::istream &stream, std::string &currentLine, std::string &vertShaderCode) const
	{
		while (std::getline(stream, currentLine) && currentLine.find(fragShaderTitle) != std::string::npos)
		{
			vertShaderCode += currentLine + '\n';
		}
	}

	void ShaderLoader::FillFragmentShaderCode(std::istream &stream, std::string &currentLine, std::string &fragShaderCode) const
	{
		while (std::getline(stream, currentLine) && currentLine.find(vertShaderTitle) != std::string::npos)
		{
			fragShaderCode += currentLine + '\n';
		}
	}
}
