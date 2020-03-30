#include <winPoint.h>



WinPoint::WinPoint()
{
}

WinPoint::~WinPoint()
{
}

void WinPoint::init()
{
	m_shape.setFillColor(m_colorActivated);
	m_shape.setRadius(m_ratio);
	m_shape.setOrigin(m_ratio, m_ratio);
}

void WinPoint::render(sf::RenderWindow& _wind)
{
	if (m_bIsActived)
	{
		_wind.draw(m_shape);
	}
}

void WinPoint::setPosition(const float& posx, const float& posy)
{
	m_position = { posx,posy };
	m_shape.setPosition(posx,posy);
}
