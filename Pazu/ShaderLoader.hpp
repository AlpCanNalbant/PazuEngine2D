#pragma once
#include "GL/glew.h"
#include "Shader.hpp"
#include "ResourceLoader.hpp"

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
		bool CreateShader(Shader& shader, std::istream &&is) const;
		void CompileShader(Shader& shader, const char* code, GLenum shaderType, GLuint& shaderID) const;
		void Link(Shader& shader, GLuint& vertShaderID, GLuint& fragShaderID) const;
		void GetActiveUniforms(Shader& shader) const;
	};
}
