namespace Pazu
{
	template<typename T>
	std::shared_ptr<T> ResourceManager::Load(const std::string &resourcePath)
	{
		if (cache[resourcePath] != nullptr)
        {
			return std::dynamic_pointer_cast<T>(cache[resourcePath]);
        }
		if constexpr (std::is_same_v<T, Shader>)
        {
			return std::dynamic_pointer_cast<T>(resourceLoaders[std::type_index(typeid(ShaderLoader))]->LoadResource(resourcePath));
        }
		else if constexpr (std::is_same_v<T, Texture>)
        {
			return std::dynamic_pointer_cast<T>(resourceLoaders[std::type_index(typeid(TextureLoader))]->LoadResource(resourcePath));
        }
		std::cout << "Invalid resource type.\n";
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
