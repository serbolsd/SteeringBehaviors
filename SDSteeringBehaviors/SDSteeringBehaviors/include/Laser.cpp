#include <Laser.h>
#include <Boid.h>
Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::init(const CDVector2& _pos1, const CDVector2& _pos2,float* _deltaTime)
{
	m_pos1 = _pos1;
	m_pos2 = _pos2;
	m_pDeltaTime = _deltaTime;
	m_sizeToPos1 = m_pos1 - m_pos2;
	m_sizeToPos2 = m_pos2 - m_pos1;
	float angle = calculateAngle(m_sizeToPos2.getnormalize());
	angle *= 180 / 3.1415f;
	m_length = m_sizeToPos1.length();
	line.setPrimitiveType(sf::PrimitiveType::Lines);
	line.resize(2);
	line[0].color = m_colorDesactivated;
	line[0].position = { m_pos1.x,m_pos1.y };
	line[0].texCoords = {50,50};
	line[1].color = m_colorDesactivated;
	line[1].position = { m_pos2.x,m_pos2.y };
	line[1].texCoords = {50,50};
	lin.setSize(sf::Vector2f( m_sizeToPos2.length(), m_ratio));
	lin.setFillColor(m_colorDesactivated);
	lin.setPosition(sf::Vector2f(m_pos1.x, m_pos1.y));
	lin.setOrigin(sf::Vector2f(0, m_ratio/2));
	lin.rotate(-angle);
}

void Laser::update(std::vector<Boid*> _boid, Boid* _player)
{
	m_elapseTime += *m_pDeltaTime;
	if (m_elapseTime > m_timeToActivate&& m_isGoingToActivated)
	{
		lin.setFillColor(m_colorActivated);
		m_isGoingToActivated = false;
		m_isActivated = true;
		m_timeActivate = m_elapseTime + m_constTimeActivate;
		return;
	}
	if (!m_isActivated)
	{
		waitForPlayer(_player);
		return;
	}
	else
	{
		if (m_elapseTime> m_timeActivate)
		{
			m_isActivated = false;
			lin.setFillColor(m_colorDesactivated);
		}
		checkBoids(_boid);
	}
	
}

void Laser::render(sf::RenderWindow& _wind)
{
	_wind.draw(line);
	_wind.draw(lin);
}

void Laser::waitForPlayer(Boid* _player)
{
	CDVector2 boidPosition = _player->getPosition();
	CDVector2 kinship1 = boidPosition - m_pos1;
	CDVector2 kinship2 = boidPosition - m_pos2;//
	float resultKinship1 = kinship1.dot(m_sizeToPos2);
	float resultKinship2 = kinship2.dot(m_sizeToPos1);
	if (resultKinship1 < 0 || resultKinship2 < 0)
	{
		return;
	}
	float proyection = kinship2.length();
	proyection /= m_sizeToPos1.length();
	if (proyection < 0)
	{
		proyection *= -1;
	}
	CD::CDVector2 nearPoint = (m_sizeToPos1 * proyection) + m_pos2;
	nearPoint -= boidPosition;
	if (nearPoint.length()<m_ratio)
	{
		m_timeToActivate = m_elapseTime+ m_constTimeToActivate;
		m_isGoingToActivated = true;
		line[0].color = m_colorActivated;
		line[1].color = m_colorActivated;
		
	}
}

void Laser::checkBoids(std::vector<Boid*> _boid)
{
	for (size_t i = 0; i < _boid.size(); i++)
	{
		if (_boid[i]->m_isDead)
		{
			continue;
		}
		CDVector2 boidPosition = _boid[i]->getPosition();
		CDVector2 kinship1 = boidPosition - m_pos1;
		CDVector2 kinship2 = boidPosition - m_pos2;//
		float resultKinship1 = kinship1.dot(m_sizeToPos2);
		float resultKinship2 = kinship2.dot(m_sizeToPos1);
		if (resultKinship1 < 0 || resultKinship2 < 0)
		{
			continue;
		}
		CDVector2 vectorProyection = boidPosition - m_pos2;
		float proyection = vectorProyection.length();
		proyection /= m_sizeToPos1.length();
		CD::CDVector2 nearPoint1 = (m_sizeToPos1 * proyection) + m_pos2;
		CDVector2 boidCollisionPoint1 = nearPoint1 - boidPosition;
		if (boidCollisionPoint1.length() < _boid[i]->getRatio() + m_ratio)
		{

			if (_boid[i]->getTypeBoid() == TYPEBOID::PLAYER)
			{
				_boid[i]->takeDamageToPlayer(_boid[i]);
			}
			else
			{
				_boid[i]->m_isDead = true;
			}
		}
		boidCollisionPoint1.normalize();
		boidCollisionPoint1 *= _boid[i]->getRatio();
		boidCollisionPoint1 += boidPosition;
		nearPoint1 -= boidCollisionPoint1;
		//float length1 = nearPoint1.length();

		CDVector2 vectorProyection2 = boidPosition - m_pos1;
		float proyection2 = vectorProyection2.length();
		proyection2 /= m_sizeToPos2.length();
		CD::CDVector2 nearPoint2 = (m_sizeToPos2 * proyection2) + m_pos1;
		CDVector2 boidCollisionPoint2 = nearPoint2 - boidPosition;
		boidCollisionPoint2.normalize();
		boidCollisionPoint2 *= _boid[i]->getRatio();
		boidCollisionPoint2 += boidPosition;
		nearPoint2 -= boidCollisionPoint2;
		float length1 = nearPoint1.length();
		float length2 = nearPoint2.length();

		if (length1 <= m_ratio|| length2  <= m_ratio)
		{
			if (_boid[i]->getTypeBoid()==TYPEBOID::PLAYER)
			{
				_boid[i]->takeDamageToPlayer(_boid[i]);
			}
			else
			{
				_boid[i]->m_isDead = true;
			}
		}
	}
}

float Laser::calculateAngle(const CDVector2& _vec)
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
