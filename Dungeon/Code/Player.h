#pragma once
# include "Map.h"


class Player
{
	Point m_pos;

public:

	Player()
	{

	}

	Player(const Point& _pos):m_pos(_pos)
	{

	}

	Point getPos()const { return m_pos; }

	void update()
	{

	}

	bool move(const MapData& _mapData,const Point& _move)
	{
		if (_mapData.getMapID(m_pos.movedBy(_move)) == MapID::FLOOR)
		{
			m_pos.moveBy(_move);
			return true;
		}

		else
		{
			return false;
		}
	}

	void drawAt(const Point& _center)const
	{
		Circle(_center, 15).draw(Palette::Red);
	}
};