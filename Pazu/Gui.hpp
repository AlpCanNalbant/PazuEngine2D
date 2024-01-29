// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "Sprite.hpp"

namespace Pazu
{
	class Input;

	class Gui : public Sprite
	{
	public:
		Gui();

	protected:
		Input *input;
	};
}
