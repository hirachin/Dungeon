#pragma once
# include "MapData.h"
# include "Player.h"

class Map
{
	MapData m_mapData;

	Player m_player;

	int m_gridLength = 50;

public:

	Map()
	{
		m_mapData = MapData(Size(50, 50));
		m_player = Player(Point(5, 5));
	}

	Map(const Size& _size)
	{
		m_mapData = MapData(_size);
		m_player = Player(Point(5, 5));
	}

	Map(const FilePath& _path)
	{
		m_mapData = MapData(_path);
		m_player = Player(Point(1, 1));
	}

	Point getPlayerPos()const { return m_player.getPos(); }

	bool playerMove(const Point& _move)
	{
		if (_move.isZero())
		{
			return false;
		}

		return m_player.move(m_mapData, _move);
	}

	Size getSize()const { return m_mapData.getSize(); }

	MapID getMapID(const Point& _pos)const
	{
		return m_mapData.getMapID(_pos);
	}

	MapID getMapID(int _x,int _y)const
	{
		return m_mapData.getMapID(_x,_y);
	}

	void draw(const Point& _pos)const
	{
		for (int y = 0; y < getSize().y; y++)
		{
			for (int x = 0; x < getSize().x; x++)
			{
				const Point pos = Point(x, y)*m_gridLength;
				const Size size = Size(m_gridLength, m_gridLength);

				Rect(pos + _pos, size).draw(getColor(m_mapData.getMapID(x, y)));
			}
		}

		drawGridLine(_pos);
	}

	void draw(int _x, int _y)const
	{
		draw(Point(_x, _y));
	}

	void draw(const Point& _pos, const Point& _drawPos,const Size& _drawSize)const
	{
		for (int y = 0; y < Min(getSize().y,_drawSize.y); y++)
		{
			for (int x = 0; x < Min(getSize().x, _drawSize.x); x++)
			{
				const Point pos = Point(x, y)*m_gridLength;
				const Size size = Size(m_gridLength, m_gridLength);

				Rect(pos + _pos, size).draw(getColor(m_mapData.getMapID(Point(x, y).movedBy(_drawPos))));
			}
		}

		drawGridLine(_pos, _drawSize);

		m_player.drawAt(((m_player.getPos() - _drawPos)*m_gridLength).movedBy(m_gridLength / 2, m_gridLength / 2));
	}

	void draw(int _x,int _y, int _drawPosX, int _drawPosY,int _drawSizeX, int _drawSizeY)const
	{
		draw(Point(_x, _y), Point(_drawPosX, _drawPosY), Size(_drawSizeX, _drawSizeY));
	}


	Color getColor(const MapID& _id)const
	{
		switch (_id)
		{
			case MapID::FLOOR:
			{
				return Palette::Green;
			}
			case MapID::WALL:
			{
				return Palette::Gray;
			}

			default:
			{
				return Palette::Black;
			}
		}
	}

	void drawGridLine(const Point& _pos)const
	{
		//‰¡ü
		for (int y = 0; y < getSize().y + 1; y++)
		{
			Line(0, y*m_gridLength, getSize().x*m_gridLength, y*m_gridLength).movedBy(_pos).draw(Palette::White);
		}

		//cü
		for (int x = 0; x < getSize().x + 1; x++)
		{
			Line(x*m_gridLength, 0, x*m_gridLength, getSize().y*m_gridLength).movedBy(_pos).draw(Palette::White);
		}
	}

	void drawGridLine(const Point& _pos ,const Size& _drawSize)const
	{	
		const Size drawMapSize = Size(Min(getSize().x, _drawSize.x), Min(getSize().y, _drawSize.y));

		//‰¡ü
		for (int y = 0; y < drawMapSize.y + 1; y++)
		{
			Line(0, y*m_gridLength, drawMapSize.x*m_gridLength, y*m_gridLength).movedBy(_pos).draw(Palette::White);
		}

		//cü
		for (int x = 0; x < drawMapSize.x + 1; x++)
		{
			Line(x*m_gridLength, 0, x*m_gridLength, drawMapSize.y*m_gridLength).movedBy(_pos).draw(Palette::White);
		}
	}

};
