// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <string>

namespace Pazu
{
	struct Configuration
	{
		std::string title{"Powered by Pazu Engine 2D"};
		int width{800}, height{600};
		int depthBits{24};
		int stencilBits{8};
		int antialiasingLevel{16};
		bool fullScreen{false};
		bool borderless{false};
	};
}
