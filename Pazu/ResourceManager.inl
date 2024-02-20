// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Pazu
{
	template<typename T>
	std::shared_ptr<T> ResourceManager::Load(const std::string &resourcePath) const
	{
		if (const auto pos = cache.find(resourcePath); pos != cache.cend())
        {
			return std::dynamic_pointer_cast<T>(pos->second);
        }
		if constexpr (std::is_same_v<T, Shader>)
        {
			return std::dynamic_pointer_cast<T>(resourceLoaders.find(typeid(ShaderLoader))->second->LoadResource(resourcePath));
        }
		else if constexpr (std::is_same_v<T, Texture>)
        {
			return std::dynamic_pointer_cast<T>(resourceLoaders.find(typeid(TextureLoader))->second->LoadResource(resourcePath));
        }
		Wcm::Log->Error("Invalid resource type.");
		return nullptr;
	}

	template<typename T>
	void ResourceManager::CacheResource(const std::string &resourcePath, const std::shared_ptr<Resource> &resource)
	{
		cache[resourcePath] = resource;
	}

	template<typename T>
	bool ResourceManager::RegisterLoader()
	{
		if (!resourceLoaders.contains(std::type_index(typeid(T))))
		{
			resourceLoaders[std::type_index(typeid(T))] = std::make_unique<T>(this);
            return true;
		}
        return false;
	}
}
