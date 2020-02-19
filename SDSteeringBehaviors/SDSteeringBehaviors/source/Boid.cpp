#include "Boid.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
	ElapsedTime += *myDesc.globalTime;
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
	if (myDesc.wander.impetu > 0)
	{
		switch (myDesc.wander.type)
		{
		case unknowWanderType:
			break;
		case WanderTypeRandom:
			newDirection +=
			wanderRandom(m_Position,m_Direction, myDesc.wander.limitsX, myDesc.wander.limitsY, myDesc.wander.impetu);
			break;
		case wanderTypeTime:
			newDirection +=
				wanderTime(m_Position,m_Direction, myDesc.wander.limitsX, myDesc.wander.limitsY, 
					myDesc.wander.impetu, ElapsedTime, myDesc.wander.timeToNextPoint);
			break;
		case WanderTypeVision:
			newDirection +=
				wander(m_Position,m_Direction, myDesc.wander.impetu,myDesc.wander.DistoToPointProyection, 
					myDesc.wander.ratio, myDesc.wander.openingAngleInDegrees);
			break;
		default:
			break;
		}
	}
	if (myDesc.followPath.impetu > 0)
	{
		newDirection +=
			FollowPath(m_Position, *myDesc.followPath.Points, myDesc.followPath.impetu, myDesc.followPath.IndexPoint, myDesc.followPath.ratio);
	}
	if (myDesc.patrol.impetu > 0)
	{
		switch (myDesc.patrol.type)
		{			
		case PatrolTypeCircuit:
			newDirection +=
				PatrolCircuit(m_Position,*myDesc.patrol.Points,myDesc.patrol.impetu,myDesc.patrol.indexPath, myDesc.patrol.Ratio,ElapsedTime ,myDesc.patrol.timeToStay);
			break;
		case PatrolTypeInverted:
			newDirection +=
				PatrolInverted(m_Position, *myDesc.patrol.Points, myDesc.patrol.impetu, myDesc.patrol.indexPath, myDesc.patrol.Ratio, ElapsedTime, myDesc.patrol.timeToStay,myDesc.patrol.bReturn);
			break;
		default:
			break;
		}
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

CD::CDVector2 Boid::wanderRandom(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 LimitsX, CD::CDVector2 LimitsY, float impetu)
{
	float x = LimitsX.x + std::rand() % (int)LimitsX.y +1;
	float y = LimitsY.x + std::rand() % (int)LimitsY.y +1;
	CD::CDVector2 point = { x,y };
	
	CD::CDVector2 F = seek(PosA,point,impetu);

	return F;
}

CD::CDVector2 Boid::wanderTime(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 LimitsX, CD::CDVector2 LimitsY, float impetu, float &timeElapsed, float TimeToNextPoint)
{
	CD::CDVector2 F;
	if (DirA == CD::CDVector2(0,0))
	{
		srand(time(NULL));
		float x = LimitsX.x + std::rand() % (int)LimitsX.y + 1;
		float y = LimitsY.x + std::rand() % (int)LimitsY.y + 1;
		
		CD::CDVector2 point = { x,y };
		F = seek(PosA,point,impetu);
		return F;
	}
	if (timeElapsed>=TimeToNextPoint)
	{
		srand(time(NULL));
		float x = LimitsX.x + std::rand() % (int)LimitsX.y + 1;
		float y = LimitsY.x + std::rand() % (int)LimitsY.y + 1;
		CD::CDVector2 point = { x,y };
		F = seek(PosA, point, impetu);
		timeElapsed = 0;
	}
	else
	{
		F = DirA.getnormalize() * impetu;
	}
	
	return F;
}

CD::CDVector2 Boid::wander(CD::CDVector2 PosA, CD::CDVector2 DirA, float impetu, float distToProyection, float ratio, float angle)
{

	CD::CDVector2 F;
	if (DirA == CD::CDVector2(0, 0))
	{
		srand(time(NULL));
		float x = std::rand() % (int)1 -0.5;
		float y =  std::rand() % (int)1 -0.5;

		CD::CDVector2 point = { x,y };
		F = seek(PosA, point, impetu);
		return F;
	}
	srand(time(NULL));
	CD::CDVector2 C = PosA + (DirA * distToProyection);
	float Adir = std::atan(DirA.y/DirA.x)*(180/3.1415);
	float Fdir = Adir + (std::rand() % (int)(angle + Adir + 1));
	Fdir -= angle / 2;
	std::cout << Adir <<std::endl;
	CD::CDVector2 posF =  { ratio * cosf(Fdir * 3.1415 / 180),ratio*sinf(Fdir * 3.1415 / 180) };
	posF += C;
	F = seek(PosA, posF,impetu);

	return F;
}

CD::CDVector2 Boid::FollowPath(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio)
{
	CD::CDVector2 v1 = PosA-Points[indexPath];
	CD::CDVector2 v2;
	CD::CDVector2 nextPoint;
	if (indexPath ==Points.size()-1)
	{
		nextPoint = Points[0];
		v2 =  Points[0]- Points[indexPath];
	}
	else
	{
		nextPoint = Points[indexPath + 1];
		v2 = Points[indexPath + 1] - Points[indexPath];
	}
	CD::CDVector2 dist = PosA - nextPoint;
	float distance = dist.length();
	if (distance <=Ratio)
	{
		indexPath++;
		if (indexPath== Points.size())
		{
			indexPath = 0;
		}
	}
	float proyection = CD::CDVector2::dot(v1,v2);
	proyection /= v2.length();
	CD::CDVector2 pathPoint=(v2*proyection)+Points[indexPath];
	CD::CDVector2 F = seek(PosA,pathPoint,impetu);
	F += seek(PosA, nextPoint,impetu);
	return F;
}

CD::CDVector2 Boid::PatrolCircuit(CD::CDVector2 PosA, std::vector<CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed, float timeToStay)
{
	CD::CDVector2 v1 = PosA - Points[indexPath];
	CD::CDVector2 v2;
	CD::CDVector2 nextPoint;
	if (indexPath == Points.size() - 1)
	{
		nextPoint = Points[0];
		v2 = Points[0] - Points[indexPath];
	}
	else
	{
		nextPoint = Points[indexPath + 1];
		v2 = Points[indexPath + 1] - Points[indexPath];
	}
	CD::CDVector2 dist = PosA - nextPoint;
	float distance = dist.length();
	if (distance <= Ratio)
	{
		if (timeElapsed<= timeToStay)
		{
			//Action;
			return	CD::CDVector2();
		}
		indexPath++;
		if (indexPath == Points.size())
		{
			indexPath = 0;
		}
	}
	else
	{
		timeElapsed = 0;
	}
	float proyection = CD::CDVector2::dot(v1, v2);
	proyection /= v2.length();
	CD::CDVector2 pathPoint = (v2 * proyection) + Points[indexPath];
	CD::CDVector2 F = seek(PosA, pathPoint, impetu);
	F += seek(PosA, nextPoint, impetu);
	return F;
}

CD::CDVector2 Boid::PatrolInverted(CD::CDVector2 PosA, std::vector<CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed, float timeToStay, bool& bReturn)
{
	CD::CDVector2 v1 = PosA - Points[indexPath];
	CD::CDVector2 v2;
	CD::CDVector2 nextPoint;
	if (bReturn)
	{
		nextPoint = Points[indexPath - 1];
		v2 = Points[indexPath]-Points[indexPath - 1];
	}
	else
	{
		nextPoint = Points[indexPath + 1];
		v2 = Points[indexPath + 1] - Points[indexPath];
	}
	
	CD::CDVector2 dist = PosA - nextPoint;
	float distance = dist.length();
	if (distance <= Ratio)
	{
		if (timeElapsed <= timeToStay)
		{
			//Action;
			return	CD::CDVector2();
		}
		if (bReturn)
		{
			indexPath--;
			if (indexPath == 0)
			{
				//indexPath++;
				bReturn = false;
			}
		}
		else
		{
			indexPath++;
			if (indexPath == Points.size()-1)
			{
				//indexPath--;
				bReturn=true;
			}
		}
	}
	else
	{
		timeElapsed = 0;
	}
	float proyection = CD::CDVector2::dot(v1, v2);
	proyection /= v2.length();
	CD::CDVector2 pathPoint = (v2 * proyection) + Points[indexPath];
	CD::CDVector2 F = seek(PosA, pathPoint, impetu);
	F += seek(PosA, nextPoint, impetu);
	return F;
}
