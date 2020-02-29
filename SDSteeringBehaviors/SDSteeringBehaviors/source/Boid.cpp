#include "Boid.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Obstacle.h"

Boid::Boid()
{
	m_Speed = 0;
}

Boid::~Boid()
{
}

void Boid::Init(BoidDescriptor _Desc)
{
	linesForObstacleEvade.setPrimitiveType(sf::LinesStrip);
	linesForObstacleEvade.resize(4);
	backLeftToObstacle.setPrimitiveType(sf::LinesStrip);
	backLeftToObstacle.resize(2);
	frontRightToObstacle.setPrimitiveType(sf::LinesStrip);
	frontRightToObstacle.resize(2);
	//shape.setPointCount(3);
	myDesc = _Desc;
	shape.setRadius(_Desc.ratio);
	shape.setOrigin(_Desc.ratio, _Desc.ratio);
	m_Speed = _Desc.Speed;
	m_Position = _Desc.Position;
	m_Direction = _Desc.Direction;
	if (m_Direction!=CD::CDVector2(0,0))
	{
		m_DirectionView = m_Direction.getnormalize();
	}
	else
	{
		m_DirectionView = _Desc.DirectionView;
	}
	Right = {m_DirectionView.y,-m_Direction.x};
	shape.setFillColor(myDesc.shapeColor);
	if (myDesc.ptr_obstacles != nullptr&& myDesc.ptr_obstacles->size()>0)
	{
		thereAreObstacles = true;
	}
	else
	{
		return;
	}
	if (myDesc.obstacleEvadeDimentions.sizeFront<myDesc.ratio)
	{
		myDesc.obstacleEvadeDimentions.sizeFront = myDesc.ratio*6;
	}
	if (myDesc.obstacleEvadeDimentions.sizeBack < myDesc.ratio)
	{
		myDesc.obstacleEvadeDimentions.sizeBack = myDesc.ratio*2;
	}
	if (myDesc.obstacleEvadeDimentions.sizeLeft < myDesc.ratio)
	{
		myDesc.obstacleEvadeDimentions.sizeLeft = myDesc.ratio*2;
	}
	if (myDesc.obstacleEvadeDimentions.sizeRight < myDesc.ratio)
	{
		myDesc.obstacleEvadeDimentions.sizeRight = myDesc.ratio*2;
	}
	shape.setPosition(m_Position.x, m_Position.y);
	CalculateImpetuForCollision();
	calculatePointsToDetecteCollision();
	calculateDimensionToDetecteCollision();
}

void Boid::Update()
{
	ElapsedTime += *myDesc.globalTime;
	CD::CDVector2 newDirection = { 0,0 };
	m_Direction = m_DirectionView * m_Speed;
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
		case TypeWander::unknowWanderType:
			break;
		case TypeWander::WanderTypeRandom:
			newDirection +=
			wanderRandom(m_Position, myDesc.wander.limitsX, myDesc.wander.limitsY, myDesc.wander.impetu);
			break;
		case TypeWander::wanderTypeTime:
			newDirection +=
				wanderTime(m_Position,m_Direction, myDesc.wander.limitsX, myDesc.wander.limitsY, 
					myDesc.wander.impetu, ElapsedTime, myDesc.wander.timeToNextPoint);
			break;
		case TypeWander::WanderTypeVision:
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
		case TypePatrol::PatrolTypeCircuit:
			newDirection +=
				PatrolCircuit(m_Position,*myDesc.patrol.Points,myDesc.patrol.impetu,myDesc.patrol.indexPath, myDesc.patrol.Ratio,ElapsedTime ,myDesc.patrol.timeToStay);
			break;
		case TypePatrol::PatrolTypeInverted:
			newDirection +=
				PatrolInverted(m_Position, *myDesc.patrol.Points, myDesc.patrol.impetu, myDesc.patrol.indexPath, myDesc.patrol.Ratio, ElapsedTime, myDesc.patrol.timeToStay,myDesc.patrol.bReturn);
			break;
		default:
			break;
		}
	}
	if (myDesc.flocking.impetuDirection > 0)
	{
		newDirection +=
			flocking(this,myDesc.flocking.Boids, myDesc.flocking.ratioVision, myDesc.flocking.impetuDirection, myDesc.flocking.impetuCohesion, myDesc.flocking.impetuSeparation);
	}
	if (myDesc.followLeader.impetuFollow > 0)
	{
		newDirection +=
			FollowTheLeader(this,myDesc.followLeader.Boids, myDesc.followLeader.ratioVision, myDesc.followLeader.impetuFollow, myDesc.followLeader.impetuEvade, myDesc.followLeader.impetuDirection, myDesc.followLeader.impetuCohesion, myDesc.followLeader.impetuSeparation, myDesc.followLeader.Leader, myDesc.followLeader.distToLeader);
	}
	if (thereAreObstacles)
	{
		newDirection +=
		obstacleCollision(this,myDesc.ptr_obstacles,impetuForCollision);
		newDirection +=
		obstacleEvade(this, myDesc.ptr_obstacles, myDesc.obstacleEvadeDimentions.impetu);
	}
	if (newDirection!=CD::CDVector2(0,0))
	{
		//newDirection = truncar(newDirection,m_Speed);
		m_Direction = Inercia(m_Direction,newDirection,myDesc.masa);
		newDirection = truncar(newDirection,m_Speed);
		m_DirectionView = m_Direction.getnormalize();
		Right = { m_DirectionView.y,-m_Direction.x };
		
	}
	else
	{
		m_Direction = CD::CDVector2(0, 0);
	}
	
	if (myDesc.arrive.impetu > 0)
	{
		newDirection = arrive(m_Position, m_Direction, *myDesc.arrive.objetive, m_Speed, myDesc.arrive.ratio,myDesc.masa);
		
		m_Direction = newDirection;
		if (newDirection != CD::CDVector2(0, 0))
		{
			//m_Direction += (newDirection * myDesc.masa);
			//m_Direction.normalize();
			m_DirectionView = m_Direction.getnormalize();
			//m_DirectionView.normalize();
			Right = { m_DirectionView.y,-m_DirectionView.x };
		}
		else
		{
			m_Direction = CD::CDVector2(0, 0);
		}
	}
	else
	{
		m_Direction *= m_Speed;
	}
	calculatePointsToDetecteCollision();
}

void Boid::Render(sf::RenderWindow& _wind)
{
	m_Position += m_Direction;
	shape.setPosition(m_Position.x, m_Position.y);
	_wind.draw(shape);
	//_wind.draw(linesForObstacleEvade);
	//_wind.draw(backLeftToObstacle);
	//_wind.draw(frontRightToObstacle);
}

void Boid::Delete()
{
	delete myDesc.seek.objetive;
	delete myDesc.flee.objetive;
	delete myDesc.arrive.objetive;
	if (myDesc.evade.objetive!=nullptr)
	{
		delete myDesc.evade.objetive;

	}
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

CD::CDVector2 Boid::arrive(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB, float Impetu, float ratio, float masa)
{
	CD::CDVector2 Dir = PosB - PosA;
	float tempImpetu = Impetu;
	if (Dir.length()<ratio)
	{
		tempImpetu = Dir.length() / ratio;
	}
	Dir.normalize();
	CD::CDVector2 F = DirA;
	CD::CDVector2 newDir = Dir;
	newDir = truncar(newDir, Impetu);
	F= Inercia(DirA, newDir, masa);;
	F *= Impetu *tempImpetu;
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
		Dir = flee(PosA,PosB,Impetu);
		Dir += flee(PosA,PPpos,Impetu);
		Dir.normalize();
		F = Dir * Impetu;
	}
	return F;
}

CD::CDVector2 Boid::wanderRandom(CD::CDVector2 PosA, CD::CDVector2 LimitsX, CD::CDVector2 LimitsY, float impetu)
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
		srand((unsigned int)time(NULL));
		float x = LimitsX.x + std::rand() % (int)LimitsX.y + 1;
		float y = LimitsY.x + std::rand() % (int)LimitsY.y + 1;
		
		CD::CDVector2 point = { x,y };
		F = seek(PosA,point,impetu);
		return F;
	}
	if (timeElapsed>=TimeToNextPoint)
	{
		srand((unsigned int)time(NULL));
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
		srand((unsigned int)time(NULL));
		float x = std::rand() % (int)1 -0.5f;
		float y =  std::rand() % (int)1 -0.5f;

		CD::CDVector2 point = { x,y };
		F = seek(PosA, point, impetu);
		return F;
	}
	srand((unsigned int)time(NULL));
	CD::CDVector2 C = PosA + (DirA * distToProyection);
	float Adir = std::atan(DirA.y/DirA.x);
	Adir *= (180 / 3.1415f);
	float Fdir = Adir + (std::rand() % (int)(angle));
	Fdir -= angle / 2;
	//std::cout << Adir <<std::endl;
	CD::CDVector2 posF =  { ratio * cosf(Fdir * 3.1415f / 180),ratio*sinf(Fdir * 3.1415f / 180) };
	posF += C;
	F = seek(PosA, posF,impetu);

	return F;
}

CD::CDVector2 Boid::FollowPath(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio)
{
	CD::CDVector2 v1 = PosA-Points[indexPath];
	CD::CDVector2 v2;
	CD::CDVector2 nextPoint;
	int index = indexPath;
	int nextindex = index + 1;;
	if (indexPath ==Points.size()-1)
	{
		nextPoint = Points[0];
		v2 =  Points[0]- Points[index];
	}
	else
	{
		nextPoint = Points[nextindex];
		v2 = Points[nextindex] - Points[index];
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
	if (proyection<0)
	{
		proyection *= -1;
	}
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
	int index = indexPath;
	int nextindex = index+1;
	if (indexPath == Points.size() - 1)
	{
		nextPoint = Points[0];
		v2 = Points[0] - Points[index];
	}
	else
	{
		nextPoint = Points[nextindex];
		v2 = Points[nextindex] - Points[index];
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
	if (proyection < 0)
	{
		proyection *= -1;
	}
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
	int index = indexPath;
	int nextindex = index+(int)1;
	int previndex = index-1;
	if (bReturn)
	{
		nextPoint = Points[previndex];
		v2 = Points[previndex]-Points[index];
	}
	else
	{
		nextPoint = Points[nextindex];
		v2 = Points[nextindex] - Points[index];
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
	if (proyection < 0)
	{
		proyection *= -1;
	}
	CD::CDVector2 pathPoint = (v2 * proyection) + Points[indexPath];
	CD::CDVector2 F = seek(PosA, pathPoint, impetu);
	F += seek(PosA, nextPoint, impetu);
	return F;
}

CD::CDVector2 Boid::Direction(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu)
{
	CD::CDVector2 F;
	int nearBoids = 0;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (A == Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vector = A->getPosition() - Boids[0][i]->getPosition();
		float dist = vector.length();
		if (dist<=ratioVision)
		{
			F += Boids[0][i]->getDirection();
			nearBoids++;
		}
	}
	if (nearBoids>0)
	{
		F /= (float)nearBoids;
		F.normalize();
		F *= impetu;
	}
	return F;
}

CD::CDVector2 Boid::Cohesion(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 CentroMasa;
	int nearBoids = 0;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (A== Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vector = A->getPosition() - Boids[0][i]->getPosition();
		float dist = vector.length();
		if (dist <= ratioVision)
		{
			CentroMasa += Boids[0][i]->getPosition();
			nearBoids++;
		}
	}
	if (nearBoids > 0)
	{
		CentroMasa /= (float)nearBoids;
		CD::CDVector2 vec = A->getPosition() - CentroMasa;
		F = seek(A->getPosition(), CentroMasa, impetu);
	}
	return F;
}

CD::CDVector2 Boid::Separation(Boid* A, std::vector<Boid*>* Boids, float impetu)
{
	CD::CDVector2 F;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (A == Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vecDistance = A->getPosition() - Boids[0][i]->getPosition();
		float dist = vecDistance.length();
		if (dist- Boids[0][i]->getRatio() <= A->getRatio())
		{
			F += flee(A->getPosition(), Boids[0][i]->getPosition(),impetu);
		}
	}
	return F;
}

CD::CDVector2 Boid::flocking(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetuDiretion, float impetuCohesion, float impetuSeparation)
{
	CD::CDVector2 F;
	F += Direction(A,Boids,ratioVision, impetuDiretion);
	F += Cohesion(A,Boids,ratioVision, impetuCohesion);
	F += Separation(A,Boids,impetuSeparation);
	//F.normalize();
	//F *= impetuDiretion;
	return F;
}

CD::CDVector2 Boid::FollowTheLeader(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetuFollow, float impetuEvade, float impetuDiretion, float impetuCohesion, float impetuSeparation, Boid* leader, float distToLeader)
{
	CD::CDVector2 F;
	CD::CDVector2 PointBehingTheLeader;
	CD::CDVector2 LeaderPos = leader->getPosition();
	CD::CDVector2 BoidAPos = A->getPosition();
	CD::CDVector2 LeaderDir = leader->getDirection();
	CD::CDVector2 LeaderDirView = leader->getDirectionView();
	LeaderDirView.normalize();
	if (LeaderDirView==CD::CDVector2 (0,0))
	{

	}
	PointBehingTheLeader = LeaderPos -(LeaderDirView *distToLeader);
	F += flocking(A,Boids,ratioVision, impetuDiretion,impetuCohesion,impetuSeparation);
	CD::CDVector2 DisToLeader;
	DisToLeader = BoidAPos - LeaderPos;
	//if (DisToLeader.length()>distToLeader)
	//{
	//}
	F += seek(BoidAPos,PointBehingTheLeader, impetuFollow);
	F += evade(BoidAPos, A->getDirection(), LeaderPos, LeaderDir, leader->getSpeed(), leader->getRatio(), impetuEvade);
	//F.normalize();
	//F *= impetuDiretion;
	return F;
}

CD::CDVector2 Boid::obstacleCollision(Boid* A, std::vector<Obstacle*>* ptr_obstacles, float Impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 vectorDist;
	CD::CDVector2 Apos=A->getPosition();
	CD::CDVector2 Bpos;
	float Aratio=A->getRatio();
	for (int i = 0; i < ptr_obstacles->size(); i++)
	{
		Bpos = ptr_obstacles[0][i]->getPosition();
		vectorDist = Apos - Bpos;
		float dist = vectorDist.length();
		if (dist - ptr_obstacles[0][i]->getRatio() <= Aratio)
		{
			F += flee(Apos, Bpos,Impetu);
		}
	}
	return F;
}

CD::CDVector2 Boid::obstacleEvade(Boid* A, std::vector<Obstacle*>* ptr_obstacles, float Impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 DistanceVector;
	CD::CDVector2 PosA=A->getPosition();
	CD::CDVector2 PosObstacle;
	float ratioVision = A->getDistanceToView();
	for (int i = 0; i < ptr_obstacles->size(); i++)
	{
		PosObstacle = ptr_obstacles[0][i]->getPosition();
		DistanceVector = PosA - PosObstacle;
		float disToObstacle = DistanceVector.length() - ptr_obstacles[0][i]->getRatio();
		if (disToObstacle< ratioVision)
		{
			if (A->detectedCollision(ptr_obstacles[0][i]))
			{
				F += flee(PosA, PosObstacle,Impetu);
			}
		}
	}
	return F;
}

CD::CDVector2 Boid::Inercia(CD::CDVector2 DirA, CD::CDVector2 newDir, float masa)
{
	CD::CDVector2 Dir;
	CD::CDVector2 vectorDirection;
	vectorDirection = DirA;
	vectorDirection += newDir * masa;
	Dir = vectorDirection.getnormalize();
	return Dir;
}

CD::CDVector2 Boid::truncar(CD::CDVector2 Dir, float speed)
{
	CD::CDVector2 Direction = Dir;
	if (Direction.length() > speed)
	{
		Direction.normalize();
		Direction *= speed;
	}
	return Direction;
}

void Boid::CalculateImpetuForCollision()
{
	impetuForCollision += myDesc.seek.impetu;
	impetuForCollision += myDesc.flee.impetu;
	impetuForCollision += myDesc.persu.impetu;
	impetuForCollision += myDesc.evade.impetu;
	impetuForCollision += myDesc.arrive.impetu;
	impetuForCollision += myDesc.wander.impetu;
	impetuForCollision += myDesc.followPath.impetu;
	impetuForCollision += myDesc.patrol.impetu;
	impetuForCollision += myDesc.flocking.impetuCohesion;
	impetuForCollision += myDesc.flocking.impetuDirection;
	impetuForCollision += myDesc.flocking.impetuSeparation;
	impetuForCollision += myDesc.followLeader.impetuCohesion;
	impetuForCollision += myDesc.followLeader.impetuDirection;
	impetuForCollision += myDesc.followLeader.impetuEvade;
	impetuForCollision += myDesc.followLeader.impetuFollow;
	impetuForCollision += myDesc.followLeader.impetuSeparation;
	impetuForCollision += 1;
	impetuForCollision *= 10;
}

void Boid::calculatePointsToDetecteCollision()
{

	frontRightCollisionPointPos = m_DirectionView*myDesc.obstacleEvadeDimentions.sizeFront;
	frontRightCollisionPointPos += Right * myDesc.obstacleEvadeDimentions.sizeRight;
	frontRightCollisionPointPos += m_Position;

	frontLeftCollisionPointPos = m_DirectionView * myDesc.obstacleEvadeDimentions.sizeFront;
	frontLeftCollisionPointPos += -Right * myDesc.obstacleEvadeDimentions.sizeLeft;
	frontLeftCollisionPointPos += m_Position;

	backRightCollisionPointPos = -m_DirectionView * myDesc.obstacleEvadeDimentions.sizeBack;
	backRightCollisionPointPos += Right * myDesc.obstacleEvadeDimentions.sizeRight;
	backRightCollisionPointPos += m_Position;

	backLeftCollisionPointPos = -m_DirectionView * myDesc.obstacleEvadeDimentions.sizeBack;
	backLeftCollisionPointPos += -Right * myDesc.obstacleEvadeDimentions.sizeLeft;
	backLeftCollisionPointPos += m_Position;

	linesForObstacleEvade[0].position = { backLeftCollisionPointPos.x,backLeftCollisionPointPos.y};
	linesForObstacleEvade[1].position = { frontLeftCollisionPointPos.x,frontLeftCollisionPointPos.y};
	linesForObstacleEvade[2].position = { frontRightCollisionPointPos.x,frontRightCollisionPointPos.y};
	linesForObstacleEvade[3].position = { backRightCollisionPointPos.x,backRightCollisionPointPos.y};
}

void Boid::calculateDimensionToDetecteCollision()
{
	sumLeftAndFronVisionObstacle =
		myDesc.obstacleEvadeDimentions.sizeFront + myDesc.obstacleEvadeDimentions.sizeBack
		+myDesc.obstacleEvadeDimentions.sizeLeft + myDesc.obstacleEvadeDimentions.sizeRight;
	sumLeftAndFronVisionObstacle *= 2;
	anche= myDesc.obstacleEvadeDimentions.sizeLeft + myDesc.obstacleEvadeDimentions.sizeRight;
	large = myDesc.obstacleEvadeDimentions.sizeFront + myDesc.obstacleEvadeDimentions.sizeBack;

	hipotenuse = sqrt((anche*anche+large*large));
}

bool Boid::detectedCollision(Obstacle* _obstacle)
{
	float ObstacleRatio = _obstacle->getRatio();
	CD::CDVector2 obstaclePosition = _obstacle->getPosition();
	CD::CDVector2 hipotenusa1= frontLeftCollisionPointPos;
	CD::CDVector2 hipotenusa2= backRightCollisionPointPos;
	CD::CDVector2 collisionPoint = m_Position- obstaclePosition;
	collisionPoint.normalize();
	collisionPoint *= ObstacleRatio;
	collisionPoint += obstaclePosition;
	//frontRightToObstacle[0].position = { frontLeftCollisionPointPos.x,frontLeftCollisionPointPos.y };
	//frontRightToObstacle[1].position = { collisionPoint.x,collisionPoint.y };
	//
	//backLeftToObstacle[0].position = { backRightCollisionPointPos.x,backRightCollisionPointPos.y };
	//backLeftToObstacle[1].position = { collisionPoint.x,collisionPoint.y };
	hipotenusa1 -= collisionPoint;
	hipotenusa2 -= collisionPoint;
	float sumOfHipotenusas =
		hipotenusa1.length()
		+ hipotenusa2.length();
	CD::CDVector2 v1 = backRightCollisionPointPos -frontRightCollisionPointPos;
	CD::CDVector2 v2 = backRightCollisionPointPos - backLeftCollisionPointPos;
	CD::CDVector2 v3 = frontLeftCollisionPointPos - frontRightCollisionPointPos;
	CD::CDVector2 v4 = frontLeftCollisionPointPos - backLeftCollisionPointPos;
	float proyection1 = CD::CDVector2::dot(v1, hipotenusa2);
	proyection1 /= v1.length();
	float proyection2 = CD::CDVector2::dot(v2, hipotenusa2);
	proyection2 /= v2.length();
	float proyection3 = CD::CDVector2::dot(v3, hipotenusa1);
	proyection3 /= v3.length();
	float proyection4 = CD::CDVector2::dot(v4, hipotenusa1);
	proyection4 /= v4.length();
	sumOfHipotenusas = sqrt(hipotenusa1.length()* hipotenusa1.length()+ hipotenusa2.length()* hipotenusa2.length());
	if (!(proyection4 <=0)&&!(proyection3 <= 0) && !(proyection2 <= 0) && !(proyection1 <= 0))
	{
		return true;
	}
	return false;
}
