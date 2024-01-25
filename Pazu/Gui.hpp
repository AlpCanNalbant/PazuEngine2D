#pragma once
#include "mathfu/glsl_mappings.h"
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
