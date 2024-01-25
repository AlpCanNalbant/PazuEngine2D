#include "Widget.hpp"
#include "Sprite.hpp"

namespace Pazu
{
	void Widget::AddGuiItem(Gui& item)
	{
		guiItems.push_back(&item);
	}

	void Widget::GrabItems()
	{
	}
}
