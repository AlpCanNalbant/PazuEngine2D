#include "App.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	App editor({.title = "Game Sample", .width = 1280, .height = 800, .borderless = false});

	editor.Run();

	return 0;
}
