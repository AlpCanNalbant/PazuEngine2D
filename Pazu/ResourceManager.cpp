// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <algorithm>
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
		RegisterAssets();
	}

	const std::string &ResourceManager::GetBasePath(bool isMemory) const
	{
		return basePaths[isMemory];
	}

	bool ResourceManager::IsRelative() const
	{
		return isRelative;
	}

	void ResourceManager::SetBasePath(const std::string &path, const std::source_location &location)
	{
		SetBasePath({path, path}, location);
	}

	void ResourceManager::SetBasePath(const std::string &path, bool isMemory, const std::source_location &location)
	{
		if (path.ends_with('/') || path.ends_with('\\'))
		{
			basePaths[isMemory] = path;
		}
		else
		{
			basePaths[isMemory] = path + Wcm::Separator;
		}
		if (isMemory)
		{
			std::replace(basePaths[1].begin(), basePaths[1].end(), '\\', '/'); // Pazu resource does not support back-slashes.
		}
		else if (!isMemory && isRelative)
		{
			basePaths[0] = (Wcm::GetBaseDirectory() / basePaths[0]).string();
		}
		projectAssetDir = Wcm::CutPath(location.file_name(), "Game").parent_path() / "Assets";
	}

	void ResourceManager::SetBasePath(const std::array<std::string, 2> &basePaths, const std::source_location &location)
	{
		for (std::size_t i = 0; i < basePaths.size(); ++i)
		{
			SetBasePath(basePaths[i], i, location);
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

    void ResourceManager::RegisterAssets()
    {
		projectAssetDir = projectAssetDir.parent_path() / basePaths[1];
		auto defaultShader = GetDefaultShader();
		const auto &defaultShaderPaths = defaultShader.second;
		std::wstring binaryResourceList = Wcm::ToQuoted(defaultShaderPaths[0]) + L' ' + Wcm::ToQuoted(defaultShaderPaths[1]) + L' ';
		Wcm::Execute(GetGeneratorPath(), L"\"--OutDir\" \"" + Wcm::GetBaseDirectory().native() + L'\"' + L" \"--ResList\" " + binaryResourceList + L"--DirList " + projectAssetDir.native());
		const auto oldMemResBaseDir = basePaths[1];
		basePaths[1].clear();
		defaultShader.first.get() = Load<Shader>(Wcm::ToString(defaultShaderPaths[0]));
		basePaths[1] = oldMemResBaseDir;
    }

    std::pair<std::reference_wrapper<std::shared_ptr<Shader>>, std::array<std::wstring, 2>> ResourceManager::GetDefaultShader() const
	{ // Passed as a return value reference to the shader pointer and relative and absoulete paths of that shader file.
		return {{DefaultShader}, {L"Assets/Shaders/default.shader", Wcm::GetSourceDirectory() / L"Assets/Shaders/default.shader"}};
	}

	std::wstring ResourceManager::GetGeneratorPath() const
	{
		return Wcm::GetSourceDirectory() / "Assets" / "ResourceGenerator.exe";
	}
}
