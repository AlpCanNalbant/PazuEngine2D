#include "App.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *args[])
{
	Wcm::Log->OutputFile = Wcm::GetBaseDirectory() / "ExampleGame.log";
	App editor({.title = "Game Sample", .width = 1280, .height = 800, .borderless = false});

	editor.Run();

	return 0;
}
