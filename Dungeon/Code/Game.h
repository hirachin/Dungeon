#pragma once

# include "SceneBase.h"
# include "Map.h"
# include "Player.h"

class Game :public MyApp::Scene
{
	Map m_map = Map(L"Data/testmap.csv");



	int count = 0;

	void init()override
	{

	}

	void update()override
	{
		const Point move = Point(Input::KeyD.pressed - Input::KeyA.pressed, Input::KeyS.pressed - Input::KeyW.pressed);

		if ((--count) <= 0)
		{
			if (m_map.playerMove(move))
			{
				count = 10;
			}
		}

		if (Input::KeyD.released || Input::KeyA.released || Input::KeyS.released || Input::KeyW.released)
		{
			count = 0;
		}

	}

	

	void draw()const override
	{
		const Size drawMapSize = Size(10, 10);

		Point drawPos = m_map.getPlayerPos() - drawMapSize / 2;
		drawPos.x = Clamp(drawPos.x, 0, m_map.getSize().x - drawMapSize.x);
		drawPos.y = Clamp(drawPos.y, 0, m_map.getSize().y - drawMapSize.y);

		m_map.draw(Point(0, 0), drawPos, drawMapSize);
	}
};