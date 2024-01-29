// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <string>

namespace Pazu
{
	class ResourceManager;

	class Resource
	{
	public:
		virtual ~Resource() = default;
	};

	class ResourceLoader
	{
	public:
		ResourceLoader(ResourceManager *mgr);
		virtual ~ResourceLoader() = default;
		virtual std::shared_ptr<Resource> LoadResource(const std::string &resourcePath) = 0;

	protected:
		ResourceManager* manager{nullptr};
	};
}
