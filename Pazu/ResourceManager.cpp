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
		std::wifstream ifs;
		std::wstring line;
		constexpr std::wstring_view diskSetting = L"LoadFromDisk=";
		constexpr std::wstring_view binarySetting = L"LoadFromBinary=";
		auto defaultShader = GetDefaultShader();
		const auto &defaultShaderPaths = defaultShader.second;
		std::wstring binaryResourceList = L'\"' + defaultShaderPaths[0] + L"\" \"" + defaultShaderPaths[1] + L"\" ";
		for (const auto &item : std::filesystem::recursive_directory_iterator(projectAssetDir))
		{
			if (item.is_regular_file())
			{
				if (const auto resInfoFile = item.path().native() + L".res"; std::filesystem::is_regular_file(resInfoFile))
				{
					ifs.open(resInfoFile.data());
					if (!ifs.is_open())
					{
						Wcm::Log->Error("Resource information file is cannot opened.").Sub("ResourceInfoFile", resInfoFile);
						continue;
					}
					while (std::getline(ifs, line))
					{
						if (const auto pos = line.find(diskSetting); pos != std::string::npos)
						{
							if (Wcm::IsSameString<wchar_t>(line.substr(pos + diskSetting.size(), 4), L"True"))
							{
								Wcm::UpdateFileContent(item.path(), Wcm::GetBaseDirectory() / Wcm::CutPath(item.path(), "Assets", true));
							}
						}
						if (const auto pos = line.find(binarySetting); pos != std::string::npos)
						{
							if (Wcm::IsSameString<wchar_t>(line.substr(pos + binarySetting.size(), 4), L"True"))
							{
								binaryResourceList += L'\"' + Wcm::CutPath(item.path(), "Assets", true).native() + L"\" \"" + item.path().native() + L"\" ";
							}
						}
					}
					ifs.close();
				}
			}
		}
		Wcm::Execute(GetGeneratorPath(), binaryResourceList);
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
