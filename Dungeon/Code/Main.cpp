
# include <Siv3D.hpp>
#include "Game.h"

void Main()
{
	Window::Resize(960, 960 * 9 / 16);
	//Window::Resize(960, 960 * 3 / 4);

	Graphics::SetBackground(Palette::Skyblue);

	MyApp manager;
	manager.add<Empty>(L"Empty");
	manager.add<Game>(L"Game");

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
