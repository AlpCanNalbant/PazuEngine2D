// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <list>
#include "Gui.hpp"

namespace Pazu
{
	class Widget : public Gui
	{
	public:
		void AddGuiItem(Gui& item);
		void GrabItems();

	private:
		std::list<Gui*> guiItems;
	};
}
