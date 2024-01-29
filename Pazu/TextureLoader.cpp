// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <iostream>
#include "SOIL2.h"
#include "Pazu/Resource.hpp"
#include "TextureLoader.hpp"
#include "ResourceManager.hpp"

namespace Pazu
{
	std::shared_ptr<Resource> TextureLoader::LoadResource(const std::string &resourcePath)
	{
		std::cout << "New texture is loading... Texture: " + resourcePath + '\n';
		Wcm::Log->Info("New texture is loading...").Sub("Texture", resourcePath);

		const auto texture = std::make_shared<Texture>();
		if (!LoadTexture(*texture, resourcePath))
		{
			return nullptr;
		}

		manager->CacheResource<Texture>(resourcePath, texture);
		return texture;
	}

	bool TextureLoader::LoadTexture(Texture& texture, const std::string &path) const
	{
		const auto res = GetResource(manager->GetBasePath(true) + path);
		if (!res)
		{
			std::cerr << "Texture is cannot loaded from in the memory trying to load from in the disk...\n";
			Wcm::Log->Info("Texture is cannot loaded from in the memory trying to load from in the disk...");
			// If we cannot load the texture file from in the memory then try to load from in the disk.
			texture.texID = SOIL_load_OGL_texture
			(
				(manager->GetBasePath() + path).c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
			);
			if (!texture.texID)
			{
				std::cerr << "Texture loading error: " << SOIL_last_result() << std::endl;
				Wcm::Log->Error("Texture loading error.").Sub("SOILError", SOIL_last_result());
				return false;
			}
		}
		else
		{
			texture.texID = SOIL_load_OGL_texture_from_memory
			(
				res.value().data(),
				res.value().length(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS
			);
			if (!texture.texID)
			{
				std::cerr << "Texture loading error: " << SOIL_last_result() << std::endl;
				Wcm::Log->Error("Texture loading error.").Sub("SOILError", SOIL_last_result());
				return false;
			}
		}

		glBindTexture(GL_TEXTURE_2D, texture.texID);

		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture.width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture.height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		return true;
	}
}
