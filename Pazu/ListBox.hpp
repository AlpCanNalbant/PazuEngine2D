// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <unordered_map>
#include <memory>
#include "Gui.hpp"

namespace Pazu
{
	class Texture;

	class ListBox final : public Gui
	{
	public:
		ListBox();
		void Update();
		void AddElements(std::string text[]);
		void SetElementTexture(Texture* texture, int index);
		void SetElementColor(mathfu::vec3 color, int index);
		void SetElementText(std::string text, int index);

	private:
		std::unique_ptr<Sprite> elementsBox;
		std::unordered_map<std::string, std::shared_ptr<Sprite>> elements;
	};
}
