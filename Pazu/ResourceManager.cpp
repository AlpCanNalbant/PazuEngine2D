#include "ResourceManager.hpp"
#include "Globals.hpp"

namespace Pazu
{
	ResourceManager::ResourceManager(const std::array<std::string, 2> &basePaths)
		: basePaths{basePaths} { }

	ResourceManager::ResourceManager(const std::string &basePath)
		: ResourceManager({basePath, basePath}) { }

	void ResourceManager::Initialize()
	{
		RegisterDefaultLoaders();
		LoadDefaultShader();
	}

	const std::string &ResourceManager::GetBasePath(bool isMemory) const
	{
		return basePaths[isMemory];
	}

	bool ResourceManager::IsRelative() const
	{
		return isRelative;
	}

	void ResourceManager::SetBasePath(const std::string &path)
	{
		SetBasePath({path, path});
	}

	void ResourceManager::SetBasePath(const std::string &path, bool isMemory)
	{
		if (*path.end() == '/')
		{
			basePaths[isMemory] = path;
		}
		else
		{
			basePaths[isMemory] = path + '/';
		}
		if (!isMemory && isRelative)
		{
			basePaths[isMemory] = (Wcm::GetBaseDirectory() / basePaths[isMemory]).string();
		}
	}

	void ResourceManager::SetBasePath(const std::array<std::string, 2> &basePaths)
	{
		for (std::size_t i = 0; i < basePaths.size(); ++i)
		{
			SetBasePath(basePaths[i], i);
		}
	}

	void ResourceManager::SetRelativeMode(bool enabled)
	{
		isRelative = enabled;
	}

	void ResourceManager::RegisterDefaultLoaders()
	{
		RegisterLoader<ShaderLoader>();
		RegisterLoader<TextureLoader>();
	}

	void ResourceManager::LoadDefaultShader()
	{
		DefaultShader = Load<Shader>("Assets/Shaders/default.shader");
	}
}
