#include "App.hpp"

int main(int argc, char *args[])
{
	App editor({.title = "Splash Screen", .width = 1280, .height = 800, .borderless = false});

	editor.Run();

	return 0;
}
