#pragma once

enum Direction { Up, Down, Left, Right };



class Position
{
	int m_x, m_y;
public:
	Position()
	{
		m_x = -1;
		m_y = -1;
	}
	Position(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	bool operator==(Position& p)
	{
		return m_x == p.m_x && m_y == p.m_y;
	}
	Position operator-(Position& p)
	{
		return Position(m_x - p.m_x, m_y - p.m_y);
	}
	int x() const { return m_x; }
	int y() const { return m_y; }
};

