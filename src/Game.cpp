#include <iostream>
#include "Window.h"

int main()
{
	Window window;
	window.Init(1024, 720, "My Minecraft Clone");
	window.Update();

	window.Terminate();
	return 0;
}
