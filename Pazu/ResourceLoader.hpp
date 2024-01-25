#pragma once
#include <string>
#include "Resource.hpp"

namespace Pazu
{
	class ResourceManager;

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
