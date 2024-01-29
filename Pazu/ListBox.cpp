// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "ListBox.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Input.hpp"

namespace Pazu
{
	ListBox::ListBox()
		: elementsBox{std::make_unique<Sprite>()}
	{
		elementsBox->SetDisableRender(true);
		elementsBox->scale = mathfu::vec2(100.0f, 500.0f);
		scale = mathfu::vec2(100.0f, 50.0f);
	}

	void ListBox::Update()
	{
		if (IsSelected(input->GetMousePosition(), input->IsMouseHit(SDL_BUTTON_LEFT)))
		{
			elementsBox->SetDisableRender(false);
		}
	}

	void ListBox::AddElements(std::string text[])
	{
	}

	void ListBox::SetElementTexture(Texture * texture, int index)
	{
	}

	void ListBox::SetElementColor(mathfu::vec3 color, int index)
	{
	}

	void ListBox::SetElementText(std::string text, int index)
	{
	}
}
