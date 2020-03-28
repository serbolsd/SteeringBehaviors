#include <Wall.h>

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::init(const CDVector2& _pos1, const CDVector2& _pos2)
{
	m_position1 = _pos1;
	m_position2 = _pos2;
	m_vectorWall = _pos2 - _pos1;
	m_vectorRightWall = { m_vectorWall.y,-m_vectorWall.x };
	m_vectorRightWall.normalize();
	m_line.setPrimitiveType(sf::LinesStrip);
	m_line.resize(2);
	m_line[0].position = { m_position1.x,m_position1.y };
	m_line[1].position = { m_position2.x,m_position2.y };
	m_angle = calculateAngle(m_vectorWall)*180/3.1415;
}

void Wall::render(sf::RenderWindow& _wind)
{
	_wind.draw(m_line);
}

float  Wall::calculateAngle(const CDVector2& _vec)
{
	float angle = 0;
	if (_vec.y > 0 || _vec.x < 0)
	{
		float sum = 3.1415f;
		float x = _vec.x;
		float y = _vec.y;
		if (_vec.y > 0 && _vec.x < 0)
		{
			angle = std::atan((-y / x));
		}
		else
		{
			if (_vec.y > 0)
			{
				//y *= -1;
			}
			else if (_vec.x < 0)
			{
				x *= -1;
				//sum *= 1.5;
			}
			angle = std::atan(-(-y / x));
		}
		if (_vec.y > 0 && _vec.x > 0)
		{
			angle = std::atan((-_vec.y / _vec.x));
			return angle;
		}
		//angle *= (180 / 3.1415f);//tranforn to degrees
		//if (_vec.y > 0 && _vec.x > 0)
		//{
		//	angle += 360;//tranforn to degrees
		//}
		//if (_vec.y > 0 && _vec.x < 0)
		//{
		//}
		angle += sum;

	}
	else
	{
		angle = std::atan((-_vec.y / _vec.x));
		//angle *= (180 / 3.1415f);//tranforn to degrees
	}
	return angle;
}