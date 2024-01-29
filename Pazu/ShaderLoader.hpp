// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "GL/glew.h"
#include "Shader.hpp"

namespace Pazu
{
	class ResourceManager;

	class ShaderLoader : public ResourceLoader
	{
	public:
		using ResourceLoader::ResourceLoader;
		std::shared_ptr<Resource> LoadResource(const std::string &resourcePath) final;

	private:
		bool LoadShader(Shader& shader, const std::string &path) const;
		bool CreateShader(Shader &shader, std::istream &&stream) const;
		void CompileShader(Shader& shader, const GLchar* code, GLenum shaderType, GLuint& shaderID) const;
		void Link(Shader& shader, GLuint& vertShaderID, GLuint& fragShaderID) const;
		void GetActiveUniforms(Shader& shader) const;
		void FillVertexShaderCode(std::istream &stream, std::string &currentLine, std::string &vertShaderCode) const;
		void FillFragmentShaderCode(std::istream &stream, std::string &currentLine, std::string &fragShaderCode) const;

		std::string_view fragShaderTitle{"FRAGMENT"}, vertShaderTitle{"VERTEX"};
	};
}
