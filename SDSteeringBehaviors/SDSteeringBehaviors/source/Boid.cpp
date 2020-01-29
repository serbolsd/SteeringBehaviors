#include "Boid.h"

Boid::Boid()
{
	m_Speed = 0;
}

Boid::~Boid()
{
}

void Boid::Init(BoidDescriptor _Desc)
{
	//shape.setPointCount(3);
	myDesc = _Desc;
	shape.setRadius(_Desc.ratio);
	m_Speed = _Desc.m_Speed;
	m_Position = _Desc.m_Position;
	m_Direction = _Desc.m_Direction;
	shape.setFillColor(myDesc.shapeColor);

	shape.setPosition(m_Position.x, m_Position.y);
}

void Boid::Update()
{
	CD::CDVector2 newDirection = { 0,0 };
	if (myDesc.seek.impetu>0)
	{
		newDirection += seek(m_Position,*myDesc.seek.objetive, myDesc.seek.impetu);
	}
	if (myDesc.flee.impetu>0)
	{
		if (myDesc.flee.ratio > 0)
		{
			newDirection += fleeRatio(m_Position, *myDesc.flee.objetive, myDesc.flee.impetu, myDesc.flee.ratio);
		}
		else
		{
			newDirection += flee(m_Position, *myDesc.flee.objetive, myDesc.flee.impetu);
		}
	}
	
	if (myDesc.evade.impetu > 0)
	{
		newDirection +=
			evade(m_Position,m_Direction, myDesc.evade.objetive->getPosition(), myDesc.evade.objetive->getDirection(), myDesc.evade.objetive->getSpeed(), myDesc.evade.timeProyection, myDesc.evade.impetu);
	}
	if (myDesc.persu.impetu > 0)
	{
		newDirection +=
			persu(m_Position, myDesc.persu.objetive->getPosition(), myDesc.persu.objetive->getDirection(), myDesc.persu.objetive->getSpeed(), myDesc.persu.timeProyection, myDesc.persu.impetu);
	}
	m_Direction = newDirection;
	m_Direction.normalize();
	m_Direction *= m_Speed;
	if (myDesc.arrive.impetu > 0)
	{
		m_Direction = arrive(m_Position, *myDesc.arrive.objetive, m_Speed, myDesc.arrive.ratio);
	}
}

void Boid::Render(sf::RenderWindow& _wind)
{
	m_Position += m_Direction;
	shape.setPosition(m_Position.x, m_Position.y);
	_wind.draw(shape);
}

void Boid::Delete()
{
	delete myDesc.seek.objetive;
	delete myDesc.flee.objetive;
	delete myDesc.arrive.objetive;
	delete myDesc.evade.objetive;
	delete myDesc.persu.objetive;
}

CD::CDVector2 Boid::seek(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu)
{
	CD::CDVector2 Dir = PosB - PosA;
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::flee(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu)
{
	CD::CDVector2 Dir = PosA - PosB;
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::fleeRatio(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu, float ratio)
{
	CD::CDVector2 Dir = PosA - PosB;
	CD::CDVector2 F = {0,0};
	if (Dir.length()<ratio)
	{
		Dir.normalize();
		F = Dir * Impetu;
	}
	return F;
}

CD::CDVector2 Boid::arrive(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu, float ratio)
{
	CD::CDVector2 Dir = PosB - PosA;
	float tempImpetu = Impetu;
	if (Dir.length()<ratio)
	{
		tempImpetu = Dir.length() / ratio;
	}
	Dir.normalize();
	CD::CDVector2 F = Dir * tempImpetu;
	return F;
}

CD::CDVector2 Boid::persu(CD::CDVector2 PosA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB, float TimeProyection, float Impetu)
{
	CD::CDVector2 PP = ( DirB * speedB * TimeProyection );
	CD::CDVector2 PPpos = PP + PosB;
	CD::CDVector2 Dist = PosB - PosA;
	CD::CDVector2 DistPP = PPpos - PosA;
	CD::CDVector2 Dir;
	CD::CDVector2 F ;

	if (DirB.length()==0)
	{

	}
	if (DistPP.length()>Dist.length())
	{
		PP *= (Dist.length() / DistPP.length());
		PPpos = PP + PosB;
	}
	Dir = PPpos - PosA;
	Dir.normalize();
	F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::evade(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB, float TimeProyection, float Impetu)
{
	CD::CDVector2 PP = (DirB * speedB * TimeProyection);
	CD::CDVector2 PPpos = PP + PosB;
	CD::CDVector2 Dist = PosA-PosB;
	CD::CDVector2 DistPP = PosA - PPpos;
	CD::CDVector2 Dir;
	CD::CDVector2 F;

	float space = CD::CDVector2::dot(DirB,DirA);
	float distToB = Dist.length();
	float distToPP = PP.length();
	if (Dist.length() > PP.length())
	{
		return F;
	}
	if (space >= 0.95 &&space<=1&&Dist.length()< DistPP.length())
	{
		Dir = { -PosB.y,PosB.x };
		Dir += Dist;
		Dir.normalize();
		F = Dir * Impetu;
	}
	else
	{
		//if (DistPP.length() > Dist.length())
		//{
		//	CD::CDVector2 V = PosB - PosA;
		//	CD::CDVector2 P = PPpos - PosA;
		//	CD::CDVector2 Q = P;
		//	//float escalar = V.length() / P.length();
		//	
		//	Dir = PosA - Q;
		//
		//	Dir.normalize();
		//	F = Dir * Impetu;
		//}
		Dir = flee(PosA,PosB,Impetu);
		Dir += flee(PosA,PPpos,Impetu);
		Dir.normalize();
		F = Dir * Impetu;
	}
	return F;
}
