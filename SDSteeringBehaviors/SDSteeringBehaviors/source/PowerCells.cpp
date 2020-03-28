#include <PowerCells.h>

PowerCells::PowerCells()
{
}

PowerCells::~PowerCells()
{
}

void PowerCells::init(const CDVector2& _position)
{
	m_position = _position;
	m_cell.setRadius(m_ratio);
	m_cell.setOrigin(m_ratio, m_ratio);
	m_cell.setPosition(m_position.x, m_position.y);
	m_cell.setFillColor(sf::Color::Blue);
}

void PowerCells::render(sf::RenderWindow& _wind)
{
	if (m_actived)
	{
		_wind.draw(m_cell);
	}
}
