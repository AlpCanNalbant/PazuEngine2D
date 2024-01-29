// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <string>
#include "Texture.hpp"

namespace Pazu
{
	class TextureLoader : public ResourceLoader
	{
	public:
		using ResourceLoader::ResourceLoader;
		std::shared_ptr<Resource> LoadResource(const std::string &resourcePath) final;

	private:
		bool LoadTexture(Texture& texture, const std::string &path) const;
	};
}
