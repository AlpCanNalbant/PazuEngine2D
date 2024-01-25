#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <array>
#include "ResourceLoader.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "ShaderLoader.hpp"
#include "TextureLoader.hpp"

namespace Pazu
{
	class ResourceManager
	{
	public:
		ResourceManager(const std::array<std::string, 2> &basePaths = {});
		ResourceManager(const std::string &basePath);
		void Initialize();
		template<typename T>
		std::shared_ptr<T> Load(const std::string &resourcePath);
		template<typename T>
		void CacheResource(const std::string &resourcePath, const std::shared_ptr<Resource> &resource);
		const std::string &GetBasePath(bool isMemory = false) const;
		bool IsRelative() const;
		void SetBasePath(const std::string &path);
		void SetBasePath(const std::string &path, bool isMemory);
		void SetBasePath(const std::array<std::string, 2> &basePaths);
		void SetRelativeMode(bool enabled);

		bool isRelative{true};

	private:
		void RegisterDefaultLoaders();
		void LoadDefaultShader();
		template<typename T>
		bool RegisterLoader();

		std::unordered_map<std::type_index, std::unique_ptr<ResourceLoader>> resourceLoaders;
		std::unordered_map<std::string, std::shared_ptr<Resource>> cache;
		std::array<std::string, 2> basePaths;
	};
}

#include "ResourceManager.inl"
