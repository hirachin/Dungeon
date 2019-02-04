#pragma once
#include<Siv3d.hpp>

enum class MapID
{
	NONE = 0,
	FLOOR,
	WALL,
};

class MapData
{
	Array<Array<MapID>> m_map;

public:

	MapData() {}

	MapData(const Size& _size) 
	{
		resize(_size);

		for (int y = 0; y < getSize().y; y++)
		{
			for (int x = 0; x < getSize().x; x++)
			{
				m_map[y][x] = MapID::FLOOR;
			}
		}

		EncloseWall();
	}

	MapData(const FilePath& _path)
	{
		load(_path);
	}

	void resize(const Size& _size)
	{
		m_map.resize(_size.y);

		for (int y = 0; y < _size.y; y++)
		{
			m_map[y].resize(_size.x);
		}
	}

	void resize(int _x, int _y)
	{
		resize(Size(_x, _y));
	}

	bool load(const FilePath& _path)
	{
		CSVReader reader(_path);

		if (!reader) { return false; }

		resize(reader.columns(0),reader.rows);

		for (int y = 0; y < getSize().y; y++)
		{
			for (int x = 0; x < getSize().x; x++)
			{
				m_map[y][x] = static_cast<MapID>(reader.get<int>(y,x));
			}
		}

		return true;
	}

	Size getSize()const
	{
		return Size(m_map[0].size(), m_map.size());
	}

	MapID getMapID(int _x, int _y)const
	{
		return m_map[_y][_x];
	}

	MapID getMapID(const Point& _pos)const
	{
		return m_map[_pos.y][_pos.x];
	}


	void EncloseWall()
	{
		for (int y = 0; y < getSize().y; y++)
		{
			m_map[y][0] = MapID::WALL;
			m_map[y][getSize().x-1] = MapID::WALL;
		}

		for (int x = 0; x < getSize().x; x++)
		{
			m_map[0][x] = MapID::WALL;
			m_map[getSize().y - 1][x] = MapID::WALL;
		}
	}
};