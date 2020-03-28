#include "Boid.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Obstacle.h"
#include <stdlib.h>
#include <playerInputs.h>
#include <Wall.h>
Boid::Boid()
{
	m_speed = 0;
}

Boid::~Boid()
{

}

void Boid::Init(const BoidDescriptor & _Desc)
{
	m_linesForObstacleEvade.setPrimitiveType(sf::LinesStrip);
	m_linesForObstacleEvade.resize(4);
	m_backLeftToObstacle.setPrimitiveType(sf::LinesStrip);
	m_backLeftToObstacle.resize(2);
	m_frontRightToObstacle.setPrimitiveType(sf::LinesStrip);
	m_frontRightToObstacle.resize(2);
	linesForObstacleEvade.setPrimitiveType(sf::LinesStrip);
	linesForObstacleEvade.resize(4);
	leftLoking.setPrimitiveType(sf::LinesStrip);;
	leftLoking.resize(2);
	rightLoking.setPrimitiveType(sf::LinesStrip);;
	rightLoking.resize(2);
	ratioLoking.setPrimitiveType(sf::LinesStrip);;
	ratioLoking.resize(2);

	//m_shape.setPointCount(3);
	m_myDesc = _Desc;
	m_shape.setRadius(_Desc.ratio);
	m_shape.setOrigin(_Desc.ratio, _Desc.ratio);
	m_speed = _Desc.Speed;
	m_position = _Desc.Position;
	m_direction = _Desc.Direction;
	m_mytype = _Desc.BoidType;
	if (m_direction!=CD::CDVector2(0,0))
	{
		m_directionView = m_direction.getnormalize();
	}
	else
	{
		m_directionView = _Desc.DirectionView;
	}
	m_right = {m_directionView.y,-m_direction.x};
	m_shape.setFillColor(m_myDesc.shapeColor);
	if (m_myDesc.ptr_obstacles != nullptr&& m_myDesc.ptr_obstacles->size()>0)
	{
		m_thereAreObstacles = true;
	}
	else
	{
		return;
	}
	if (m_myDesc.obstacleEvadeDimentions.sizeFront<m_myDesc.ratio)
	{
		m_myDesc.obstacleEvadeDimentions.sizeFront = m_myDesc.ratio*6;
	}
	if (m_myDesc.obstacleEvadeDimentions.sizeBack < m_myDesc.ratio)
	{
		m_myDesc.obstacleEvadeDimentions.sizeBack = m_myDesc.ratio*2;
	}
	if (m_myDesc.obstacleEvadeDimentions.sizeLeft < m_myDesc.ratio)
	{
		m_myDesc.obstacleEvadeDimentions.sizeLeft = m_myDesc.ratio*2;
	}
	if (m_myDesc.obstacleEvadeDimentions.sizeRight < m_myDesc.ratio)
	{
		m_myDesc.obstacleEvadeDimentions.sizeRight = m_myDesc.ratio*2;
	}
	m_shape.setPosition(m_position.x, m_position.y);
	CalculateImpetuForCollision();
	calculatePointsToDetecteCollision();
	calculateDimensionToDetecteCollision();
	m_pStateMachine = m_myDesc.pStateMachine;
	if (m_pStateMachine !=nullptr)
	{
		m_pMyState = m_pStateMachine->getIdleState();
	}
	if (m_mytype==TYPEBOID::PLAYER)
	{
		initLifeBars();
	}
	if (m_mytype == TYPEBOID::TORRET)
	{
		
		m_LaserTooret.setSize(sf::Vector2f(m_myDesc.ratioToLooking - m_myDesc.ratio, m_ratioLaserTorret));
		m_LaserTooret.setOrigin(sf::Vector2f(0, m_ratioLaserTorret / 2));
		m_LaserTooret.setFillColor(sf::Color::Red);
		float angle = calculateAngle(m_directionView.getnormalize());
		angle *= 180 / 3.1415f;
		m_LaserTooret.setRotation(-angle);
		updateLaserTorret(m_myDesc.pPlayer);
	}
	m_ratioDetection.setRadius(m_myDesc.ratioToLooking);
	m_ratioDetection.setOrigin(m_myDesc.ratioToLooking, m_myDesc.ratioToLooking);
	m_ratioDetection.setFillColor(sf::Color(125,0,0,100));
}

void Boid::Update()
{
	if (m_isDead)
	{
		return;
	}
	m_elapsedTime += *m_myDesc.globalTime;
	newDirection = { 0,0 };
	//m_direction = m_directionView * m_speed;
	if (m_mytype==TYPEBOID::PLAYER&& m_pStateMachine!=nullptr)
	{
		PlayerInput::onUpdate(*this);
		if (newDirection == CD::CDVector2(0, 0))
		{
			m_direction = { 0,0 };
		}
		CD::CDVector2 pointToSeek= newDirection +m_position;
		m_eMyCurrentState=m_pMyState->onUpdate(this);
		m_pStateMachine->updateState(*this);
		//updateForEveryone();
		m_eMyPastState = m_eMyCurrentState;
		if (m_myDesc.pWalls != nullptr)
		{
			wallCollision(m_myDesc.pWalls);
		}
		return;
	}
	else if (m_mytype != TYPEBOID::UNKNOWBOID && m_pStateMachine != nullptr)
	{
		m_eMyCurrentState = m_pMyState->onUpdate(this);
		m_pStateMachine->updateState(*this);
		//updateForEveryone();
		m_eMyPastState = m_eMyCurrentState;
		if (m_myDesc.pWalls!=nullptr)
		{
			wallCollision(m_myDesc.pWalls);
		}
		return;
	}
	if (m_myDesc.seek.impetu>0)
	{
		newDirection += seek(*m_myDesc.seek.objetive, m_myDesc.seek.impetu);
	}
	if (m_myDesc.flee.impetu>0)
	{
		if (m_myDesc.flee.ratio > 0)
		{
			newDirection += fleeRatio(*m_myDesc.flee.objetive, m_myDesc.flee.impetu, m_myDesc.flee.ratio);
		}
		else
		{
			newDirection += flee(*m_myDesc.flee.objetive, m_myDesc.flee.impetu);
		}
	}
	if (m_myDesc.evade.impetu > 0)
	{
		newDirection +=
			evade(m_myDesc.evade.objetive->getPosition(), m_myDesc.evade.objetive->getDirection(), m_myDesc.evade.objetive->getSpeed(), m_myDesc.evade.timeProyection, m_myDesc.evade.impetu);
	}
	if (m_myDesc.persu.impetu > 0)
	{
		newDirection +=
			persu(m_myDesc.persu.objetive->getPosition(), m_myDesc.persu.objetive->getDirection(), m_myDesc.persu.objetive->getSpeed(), m_myDesc.persu.timeProyection, m_myDesc.persu.impetu);
	}
	if (m_myDesc.wander.impetu > 0)
	{
		switch (m_myDesc.wander.type)
		{
		case TypeWander::unknowWanderType:
			break;
		case TypeWander::WanderTypeRandom:
			newDirection +=
			wanderRandom(m_myDesc.wander.limitsX, m_myDesc.wander.limitsY, m_myDesc.wander.impetu);
			break;
		case TypeWander::wanderTypeTime:
			newDirection +=
				wanderTime(m_myDesc.wander.limitsX, m_myDesc.wander.limitsY, 
					m_myDesc.wander.impetu, m_myDesc.wander.timeToNextPoint);
			break;
		case TypeWander::WanderTypeVision:
			newDirection +=
				wander( m_myDesc.wander.impetu,m_myDesc.wander.DistoToPointProyection, 
					m_myDesc.wander.ratio, m_myDesc.wander.openingAngleInDegrees);
			break;
		default:
			break;
		}
	}
	if (m_myDesc.followPath.impetu > 0)
	{
		newDirection +=
			FollowPath(*m_myDesc.followPath.Points, m_myDesc.followPath.impetu, m_myDesc.followPath.IndexPoint, m_myDesc.followPath.ratio);
	}
	if (m_myDesc.patrol.impetu > 0)
	{
		switch (m_myDesc.patrol.type)
		{			
		case TypePatrol::PatrolTypeCircuit:
			newDirection +=
				PatrolCircuit(*m_myDesc.patrol.Points,m_myDesc.patrol.impetu,m_myDesc.patrol.indexPath, m_myDesc.patrol.Ratio,m_elapsedTime ,m_myDesc.patrol.timeToStay);
			break;
		case TypePatrol::PatrolTypeInverted:
			newDirection +=
				PatrolInverted(*m_myDesc.patrol.Points, m_myDesc.patrol.impetu, m_myDesc.patrol.indexPath, m_myDesc.patrol.Ratio, m_elapsedTime, m_myDesc.patrol.timeToStay,m_myDesc.patrol.bReturn);
			break;
		default:
			break;
		}
	}
	if (m_myDesc.flocking.impetuDirection > 0)
	{
		newDirection +=
			flocking(m_myDesc.flocking.Boids, m_myDesc.flocking.ratioVision, m_myDesc.flocking.impetuDirection, m_myDesc.flocking.impetuCohesion, m_myDesc.flocking.impetuSeparation);
	}
	if (m_myDesc.followLeader.impetuFollow > 0)
	{
		newDirection +=
			FollowTheLeader(m_myDesc.followLeader.Boids, m_myDesc.followLeader.ratioVision, m_myDesc.followLeader.impetuFollow, m_myDesc.followLeader.impetuEvade, m_myDesc.followLeader.impetuDirection, m_myDesc.followLeader.impetuCohesion, m_myDesc.followLeader.impetuSeparation, m_myDesc.followLeader.Leader, m_myDesc.followLeader.distToLeader);
	}
	if (m_thereAreObstacles)
	{
		newDirection +=
		obstacleCollision(m_myDesc.ptr_obstacles,m_impetuForCollision);
		newDirection +=
		obstacleEvade( m_myDesc.ptr_obstacles, m_myDesc.obstacleEvadeDimentions.impetu);
	}
	if (newDirection!=CD::CDVector2(0,0))
	{
		//newDirection = truncar(newDirection,m_speed);
		m_direction = Inercia(newDirection);
		newDirection = truncar(newDirection,m_speed);
		m_directionView = m_direction.getnormalize();
		m_right = { m_directionView.y,-m_directionView.x };
		
	}
	else
	{
		m_direction = CD::CDVector2(0, 0);
	}
	
	if (m_myDesc.arrive.impetu > 0)
	{
		newDirection = arrive(*m_myDesc.arrive.objetive, m_myDesc.arrive.ratio,m_myDesc.masa);
		
		m_direction = newDirection;
		if (newDirection != CD::CDVector2(0, 0))
		{
			//m_direction += (newDirection * m_myDesc.masa);
			//m_direction.normalize();
			m_directionView = m_direction.getnormalize();
			//m_directionView.normalize();
			m_right = { m_directionView.y,-m_directionView.x };
		}
		else
		{
			m_direction = CD::CDVector2(0, 0);
		}
	}
	else
	{
		m_direction *= m_speed;
	}
	calculatePointsToDetecteCollision();
}

void Boid::Render(sf::RenderWindow& _wind)
{
	if (m_isDead)
	{
		return;
	}
	m_position += m_direction;
	m_shape.setPosition(m_position.x, m_position.y);
	if (m_mytype != TYPEBOID::PLAYER && m_mytype != TYPEBOID::UNKNOWBOID)
	{
		m_ratioDetection.setPosition(m_position.x, m_position.y);
		_wind.draw(m_ratioDetection);
	}
	_wind.draw(m_shape);
	_wind.draw(linesForObstacleEvade);
	if (m_mytype!=TYPEBOID::PLAYER&& m_mytype != TYPEBOID::UNKNOWBOID)
	{
		_wind.draw(leftLoking);
		_wind.draw(rightLoking);
		_wind.draw(ratioLoking);
	}
	else if (m_mytype == TYPEBOID::PLAYER)
	{
		for (size_t i = 0; i < m_maxLife; i++)
		{
			_wind.draw(lifeBars[i]);
		}
	}
	if (m_mytype==TYPEBOID::TORRET)
	{
		_wind.draw(m_LaserTooret);
	}
	//_wind.draw(backLeftToObstacle);
	//_wind.draw(frontRightToObstacle);
}

void Boid::Delete()
{
	delete m_myDesc.seek.objetive;
	delete m_myDesc.flee.objetive;
	delete m_myDesc.arrive.objetive;
	if (m_myDesc.evade.objetive!=nullptr)
	{
		delete m_myDesc.evade.objetive;

	}
	delete m_myDesc.persu.objetive;
}

CD::CDVector2 Boid::seek(CD::CDVector2 PosB, float impetu)
{
	CD::CDVector2 Dir = PosB - m_position;
	Dir.normalize();
	CD::CDVector2 F = Dir * impetu;
	return F;
}

CD::CDVector2 Boid::flee(CD::CDVector2 PosB, float impetu)
{
	CD::CDVector2 Dir = m_position - PosB;
	Dir.normalize();
	CD::CDVector2 F = Dir * impetu;
	return F;
}

CD::CDVector2 Boid::fleeRatio(CD::CDVector2 PosB, float impetu,float ratio)
{
	CD::CDVector2 Dir = m_position - PosB;
	CD::CDVector2 F = {0,0};
	if (Dir.length()< ratio)
	{
		Dir.normalize();
		F = Dir * impetu;
	}
	return F;
}

CD::CDVector2 Boid::arrive(CD::CDVector2 PosB, float impetu, float ratio)
{
	CD::CDVector2 Dir = PosB - m_position;
	float tempImpetu = impetu;
	if (Dir.length()< ratio)
	{
		tempImpetu = Dir.length() / ratio;
	}
	Dir.normalize();
	CD::CDVector2 F = m_direction;
	CD::CDVector2 newDir = Dir;
	newDir = truncar(newDir, impetu);
	F= Inercia(newDir);
	F *= impetu *tempImpetu;
	return F;
}

CD::CDVector2 Boid::persu(CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB, float TimeProyection, float impetu)
{
	CD::CDVector2 PP = ( DirB * speedB * TimeProyection );
	CD::CDVector2 PPpos = PP + PosB;
	CD::CDVector2 Dist = PosB - m_position;
	CD::CDVector2 DistPP = PPpos - m_position;
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
	Dir = PPpos - m_position;
	Dir.normalize();
	F = Dir * impetu;
	return F;
}

CD::CDVector2 Boid::evade( CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB, float TimeProyection, float impetu)
{
	CD::CDVector2 PP = (DirB * speedB * TimeProyection);
	CD::CDVector2 PPpos = PP + PosB;
	CD::CDVector2 Dist = m_position -PosB;
	CD::CDVector2 DistPP = m_position - PPpos;
	CD::CDVector2 Dir;
	CD::CDVector2 F;

	float space = CD::CDVector2::dot(DirB,m_direction);
	if (Dist.length() > PP.length())
	{
		return F;
	}
	if (space >= 0.95 &&space<=1&&Dist.length()< DistPP.length())
	{
		Dir = { -PosB.y,PosB.x };
		Dir += Dist;
	}
	else
	{
		Dir = flee(PosB, impetu);
		Dir += flee(PPpos, impetu);
	}
	Dir.normalize();
	F = Dir * impetu;
	return F;
}

CD::CDVector2 Boid::wanderRandom(CD::CDVector2 LimitsX, CD::CDVector2 LimitsY, float impetu)
{
	srand((unsigned int)time(NULL));
	float x = LimitsX.x + std::rand() % (int)LimitsX.y +1;
	float y = LimitsY.x + std::rand() % (int)LimitsY.y +1;
	CD::CDVector2 point = { x,y };
	
	CD::CDVector2 F = seek(point,impetu);

	return F;
}

CD::CDVector2 Boid::wanderTime(CD::CDVector2 LimitsX, CD::CDVector2 LimitsY, float impetu, float TimeToNextPoint)
{
	CD::CDVector2 F;
	srand((unsigned int)time(NULL));
	if (m_elapsedTime>=TimeToNextPoint|| m_direction == CD::CDVector2(0, 0))
	{
		float x = LimitsX.x + std::rand() % (int)LimitsX.y + 1;
		float y = LimitsY.x + std::rand() % (int)LimitsY.y + 1;
		CD::CDVector2 point = { x,y };
		F = seek(point, impetu);
		m_elapsedTime = 0;
	}
	else
	{
		F = m_direction.getnormalize() * impetu;
	}
	
	return F;
}

CD::CDVector2 Boid::wander(float impetu, float distToProyection, float ratio, float angle)
{

	CD::CDVector2 F;
	srand((unsigned int)time(NULL));
	if (m_direction == CD::CDVector2(0, 0))
	{
		float x = -0.5f + (std::rand() / RAND_MAX);
		float y = -0.5f + (std::rand() / RAND_MAX);

		CD::CDVector2 point = { x,y };
		F = seek(point, impetu);
		return F;
	}
	
	CD::CDVector2 C = m_position + (m_direction * distToProyection);
	float Adir = std::atan(m_direction.y/ m_direction.x);
	Adir *= (180 / 3.1415f);
	float Fdir = Adir + (std::rand() % (int)(angle));
	Fdir -= angle / 2;
	//std::cout << Adir <<std::endl;
	CD::CDVector2 posF =  { ratio * cosf(Fdir * degTorad),ratio*sinf(Fdir * degTorad) };
	posF += C;
	F = seek(posF,impetu);

	return F;
}

CD::CDVector2 Boid::FollowPath(std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio)
{
	CD::CDVector2 v1 = m_position-Points[indexPath];
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
	CD::CDVector2 dist = m_position - nextPoint;
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
	CD::CDVector2 F = seek(pathPoint,impetu);
	F += seek( nextPoint,impetu);
	return F;
}

CD::CDVector2 Boid::PatrolCircuit(std::vector<CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed, float timeToStay)
{
	CD::CDVector2 v1 = m_position - Points[indexPath];
	CD::CDVector2 v2;
	CD::CDVector2 nextPoint;
	int index = indexPath;
	int nextindex = index+1;nextPoint = Points[nextindex];
		v2 = Points[nextindex] - Points[index];
	if (indexPath == Points.size() - 1)
	{
		nextPoint = Points[0];
		v2 = Points[0] - Points[index];
	}
	
	CD::CDVector2 dist = m_position - nextPoint;
	float distance = dist.length();
	if (distance <= Ratio)
	{
		if (timeElapsed<= timeToStay)
		{
			//Action;
			return	CD::CDVector2();
		}
		++indexPath;
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
	CD::CDVector2 F = seek(pathPoint, impetu);
	F += seek(nextPoint, impetu);
	return F;
}

CD::CDVector2 Boid::PatrolInverted(std::vector<CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed, float timeToStay, bool& bReturn)
{
	CD::CDVector2 v1 = m_position - Points[indexPath];
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
	
	CD::CDVector2 dist = m_position - nextPoint;
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
	CD::CDVector2 F = seek(pathPoint, impetu);
	F += seek(nextPoint, impetu);
	return F;
}

CD::CDVector2 Boid::Direction(std::vector<Boid*>* Boids, float ratioVision, float impetu)
{
	CD::CDVector2 F;
	int nearBoids = 0;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (this == Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vector = m_position - Boids[0][i]->getPosition();
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

CD::CDVector2 Boid::Cohesion( std::vector<Boid*>* Boids, float ratioVision, float impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 CentroMasa;
	int nearBoids = 0;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (this== Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vector = m_position - Boids[0][i]->getPosition();
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
		CD::CDVector2 vec = m_position - CentroMasa;
		F = seek(CentroMasa, impetu);
	}
	return F;
}

CD::CDVector2 Boid::Separation(std::vector<Boid*>* Boids, float impetu)
{
	CD::CDVector2 F;
	for (int i = 0; i < Boids->size(); i++)
	{
		if (this == Boids[0][i])
		{
			continue;
		}
		CD::CDVector2 vecDistance = m_position - Boids[0][i]->getPosition();
		float dist = vecDistance.length();
		if (dist- Boids[0][i]->getRatio() <= m_myDesc.ratio)
		{
			F += flee(Boids[0][i]->getPosition(),impetu);
		}
	}
	return F;
}

CD::CDVector2 Boid::flocking(std::vector<Boid*>* Boids, float ratioVision, float impetuDiretion, float impetuCohesion, float impetuSeparation)
{
	CD::CDVector2 F;
	F += Direction(Boids,ratioVision, impetuDiretion);
	F += Cohesion(Boids,ratioVision, impetuCohesion);
	F += Separation(Boids,impetuSeparation);
	//F.normalize();
	//F *= impetuDiretion;
	return F;
}

CD::CDVector2 Boid::FollowTheLeader(std::vector<Boid*>* Boids, float ratioVision, float impetuFollow, float impetuEvade, float impetuDiretion, float impetuCohesion, float impetuSeparation, Boid* leader, float distToLeader)
{
	CD::CDVector2 F;
	CD::CDVector2 PointBehingTheLeader;
	CD::CDVector2 LeaderPos = leader->getPosition();
	CD::CDVector2 LeaderDir = leader->getDirection();
	CD::CDVector2 LeaderDirView = leader->getDirectionView();
	LeaderDirView.normalize();
	if (LeaderDirView==CD::CDVector2 (0,0))
	{

	}
	PointBehingTheLeader = LeaderPos -(LeaderDirView *distToLeader);
	F += flocking(Boids,ratioVision, impetuDiretion,impetuCohesion,impetuSeparation);
	CD::CDVector2 DisToLeader;
	DisToLeader = m_position - LeaderPos;
	//if (DisToLeader.length()>distToLeader)
	//{
	//}
	F += seek(PointBehingTheLeader, impetuFollow);
	F += evade(LeaderPos, LeaderDir, leader->getSpeed(), leader->getRatio(), impetuEvade);
	//F.normalize();
	//F *= impetuDiretion;
	return F;
}

CD::CDVector2 Boid::obstacleCollision(std::vector<Obstacle*>* ptr_obstacles, float Impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 vectorDist;
	CD::CDVector2 Bpos;
	for (int i = 0; i < ptr_obstacles->size(); i++)
	{
		Bpos = ptr_obstacles[0][i]->getPosition();
		vectorDist = m_position - Bpos;
		float dist = vectorDist.length();
		if (dist - ptr_obstacles[0][i]->getRatio() <= m_myDesc.ratio)
		{
			F += flee(Bpos,Impetu);
		}
	}
	return F;
}

CD::CDVector2 Boid::obstacleEvade(std::vector<Obstacle*>* ptr_obstacles, float Impetu)
{
	CD::CDVector2 F;
	CD::CDVector2 DistanceVector;
	CD::CDVector2 PosObstacle;
	float ratioVision = m_myDesc.obstacleEvadeDimentions.sizeFront;
	for (int i = 0; i < ptr_obstacles->size(); i++)
	{
		PosObstacle = ptr_obstacles[0][i]->getPosition();
		DistanceVector = m_position - PosObstacle;
		float disToObstacle = DistanceVector.length() - ptr_obstacles[0][i]->getRatio();
		if (disToObstacle< ratioVision)
		{
			if (detectedCollision(ptr_obstacles[0][i]))
			{
				F += flee(PosObstacle,Impetu);
			}
		}
	}
	return F;
}

CD::CDVector2 Boid::wallCollision(std::vector<Wall*> *_walls)
{
	CDVector2 frontMidDir=m_position+ m_direction+(m_direction.getnormalize()*m_myDesc.ratio);
	CDVector2 frontLeftDir=m_position-(m_right*m_myDesc.ratio)+m_direction + (m_direction.getnormalize() * m_myDesc.ratio);
	CDVector2 frontLeftPos=m_position-(m_right*m_myDesc.ratio);
	CDVector2 frontRightDir = m_position + (m_right * m_myDesc.ratio) + m_direction + (m_direction.getnormalize() * m_myDesc.ratio);
	CDVector2 frontRightPos = m_position + (m_right * m_myDesc.ratio);
	for (size_t i = 0; i < _walls->size(); i++)
	{
		CD::CDVector2 wallPivot = _walls[0][i]->getPos1();
		float compareFM, compareLM, compareRM = 0;
		compareFM = wallPivot.dot(frontMidDir);
		compareLM = wallPivot.dot(frontLeftDir);
		compareRM = wallPivot.dot(frontRightDir);
		if (compareFM<0&& compareLM<0&& compareRM<0)
		{
			continue;
		}
		CDVector2 wallVector = _walls[0][i]->getWallVector();
		CDVector2 wallToPos = m_position - wallPivot;
		CDVector2 wallToDir = frontMidDir - wallPivot;
		float angle1, angle2,angleWall;
		angleWall = _walls[0][i]->getAngle();
		angle1 = calculateAngle(wallToPos);
		angle1 *= 180.0f / 3.1415f;
		if (angle1<0)
		{
			angle1 = 360 - angle1;
		}
		angle2 = calculateAngle(wallToDir);
		angle2 *= 180.0f / 3.1415f;
		if (angle2 < 0)
		{
			angle2 = 360 - angle2;
		}
		if (!(angle1< angleWall&&angle2>angleWall)&& !(angle1> angleWall && angle2<angleWall))
		{
			return CD::CDVector2();
		}
		float proyection1 = wallToPos.length()/wallVector.length();
		float proyection2 = wallToDir.length() / wallVector.length();
		if (proyection1>1 &&proyection2>1 )
		{
			return CD::CDVector2();
		}
		CDVector2 nearPoint = (wallVector * proyection1)+wallPivot;
		CDVector2 DirToNearPoint = nearPoint - m_position;
		float distanceToNearPoint = DirToNearPoint.length();
		if (distanceToNearPoint <m_myDesc.ratio)
		{
			m_direction = { 0,0 };
			CDVector2 newPos = m_position - nearPoint;
			newPos.normalize();
			newPos *= m_myDesc.ratio;
			m_position = newPos + nearPoint;
			return CD::CDVector2();
		}

		float y = calculateAngle(DirToNearPoint.getnormalize());
		y = sin(y);
		y *= distanceToNearPoint;
		distanceToNearPoint += y;
		CDVector2 newNearPoint = nearPoint - wallPivot;
		float newLenght = newNearPoint.length()+y;
		proyection1 = newLenght / wallVector.length();
		if (proyection1>1)
		{
			return CD::CDVector2();
		}
		nearPoint = (wallVector * proyection1) + wallPivot;

		m_direction = { 0,0 };
		CDVector2 newPos = m_position-nearPoint;
		newPos.normalize();
		newPos *= m_myDesc.ratio;
		m_position = newPos + nearPoint;
	}
	
	return CD::CDVector2();
}

bool Boid::lookingForPlayer(Boid* objetive, float angle, float ratio)
{
	CDVector2 objetivePos = objetive->getPosition();
	CD::CDVector2 collisionPoint = m_position - objetivePos;
	collisionPoint.normalize();
	collisionPoint *= objetive->getRatio();
	collisionPoint += objetivePos;
	CDVector2 vectorToObjetive = collisionPoint - m_position;
	CDVector2 vectorToCheckObjetive = collisionPoint - m_position;
	float magnitude = vectorToObjetive.length();
	vectorToCheckObjetive.normalize();
	float parentesco = vectorToCheckObjetive.dot(m_directionView);

	float aApertura = angle * degTorad / 2;

	float apertura = m_directionView.length() * sin(aApertura);
	CDVector2 right = (-m_right * apertura) + m_directionView;
	CDVector2 left = (m_right * apertura) + m_directionView;
	CDVector2 mid = (m_directionView*ratio)+m_position;
	left *= ratio;
	left += m_position;
	right *= ratio;
	right += m_position;

	ratioLoking[0].position = leftLoking[0].position = rightLoking[0].position = { m_position.x,m_position.y };
	leftLoking[1].position = { left.x,left.y };
	rightLoking[1].position = { right.x,right.y };
	ratioLoking[1].position = { mid.x , mid.y};
	if (ratio< magnitude|| parentesco<0)
	{
		return false;
	}
	float Adir = calculateAngle(m_directionView);
	vectorToObjetive.normalize();

	
	float AtoObjetive = calculateAngle(vectorToObjetive);


	float Adir1 = Adir;
	float Adir2 = Adir;

	Adir1 -= aApertura;
	Adir2 += aApertura;
	if (AtoObjetive >= Adir1 && AtoObjetive <= Adir2)
	{
		std::cout << "wachando";
		return true;
	}
	//if (m_directionView.x < 0)
	//{
	//	
	//}
	//else
	//{
	//	if (AtoObjetive <= Adir1 && AtoObjetive >= Adir2)
	//	{
	//		std::cout << "wachando";
	//		return true;
	//	}
	//}
	
	//std::cout << Adir <<std::endl;
	//CD::CDVector2 posF = { ratio * cosf(Fdir * degTorad),ratio * sinf(Fdir * degTorad) };
	//posF += C;
	return false;
}

bool Boid::playerInRange(Boid* objetive, float ratio)
{
	CDVector2 objetivePos = objetive->getPosition();
	CD::CDVector2 collisionPoint = m_position - objetivePos;
	collisionPoint.normalize();
	collisionPoint *= objetive->getRatio();
	collisionPoint += objetivePos;
	CDVector2 vectorToObjetive = collisionPoint - m_position;
	CDVector2 vectorToCheckObjetive = collisionPoint - m_position;
	float magnitude = vectorToObjetive.length();

	if (ratio < magnitude )
	{
		return false;
	}
	return true;
}

bool Boid::isPlayerNear(Boid* objetive)
{
	float sumRatios = m_myDesc.ratio + objetive->getRatio();
	CDVector2 distanceVec = m_position - objetive->getPosition();
	if (distanceVec.length()<= sumRatios)
	{
		return true;
	}
	return false;
}

CD::CDVector2 Boid::Inercia(CD::CDVector2 newDir)
{
	CD::CDVector2 Dir;
	CD::CDVector2 vectorDirection;
	vectorDirection = m_direction;
	vectorDirection += newDir * m_myDesc.masa;
	Dir = vectorDirection.getnormalize();
	return Dir;
}

CD::CDVector2 Boid::truncar(CD::CDVector2 Dir, float speed)
{
	//if (m_direction.length() > m_speed)
	//{
	//}
	m_direction.normalize();
	m_direction *= speed;
	return m_direction;
}

void Boid::updateForWalking()
{
	m_pStateMachine->updateState(*this);
	if (m_thereAreObstacles)
	{
		newDirection +=
			obstacleCollision(m_myDesc.ptr_obstacles, m_impetuForCollision);
		newDirection +=
			obstacleEvade(m_myDesc.ptr_obstacles, m_myDesc.obstacleEvadeDimentions.impetu);
	}
	if (newDirection != CD::CDVector2(0, 0))
	{
		//newDirection = truncar(newDirection,m_speed);
		m_direction = Inercia(newDirection);
		m_direction = truncar(newDirection, m_speed);
		//m_right = { m_directionView.y,-m_direction.x };
		m_directionView = m_direction.getnormalize();

	}
	else
	{
		m_direction = CD::CDVector2(0, 0); 
	}
	m_right.x = m_directionView.y;
	m_right.y = -m_directionView.x;
	calculatePointsToDetecteCollision();
}

void Boid::updateForLoking()
{
	m_right.x = m_directionView.y;
	m_right.y = -m_directionView.x;
	calculatePointsToDetecteCollision();
}

void Boid::applyDamageToPlayer(Boid* _player)
{
	_player->takeDamageToPlayer();
}

void Boid::takeDamageToPlayer()
{
	if (m_elapsedTime> m_timeToTakeDamage)
	{
		m_timeToTakeDamage = m_constTimeToTakeDamage + m_elapsedTime;
		m_life -= 1;
		lifeBars[m_life].setFillColor(sf::Color::Red);
		if (m_life <= 0)
		{
			m_isDead;
		}
	}
	
}

void Boid::rotate()
{
	if (!m_waitingForNexRotate)
	{
		//
		srand((unsigned int)time(NULL));
		float x = (std::rand() & 10);
		float y = (std::rand() & 10);
		while (x<m_directionView.x*10+4&& x > m_directionView.x * 10 - 4)
		{
			x = (std::rand() & 10);
		}
		while (y<m_directionView.y * 10 + 4 && y > m_directionView.y * 10 - 4)
		{
			y = (std::rand() & 10);
		}
		x -= 5;
		y -= 5;
		x /= 5;
		y /= 5;
		m_pointToView = { x,y };
		m_pointToView.normalize();
		goingToPos = true;
		m_waitingForNexRotate = true;
		m_pointViewed = m_directionView;
	}
	else
	{
		if (goingToPos)
		{

			CD::CDVector2 vectorDirection;
			vectorDirection = m_pointToView;
			vectorDirection -= m_pointViewed;
			vectorDirection.normalize();
			vectorDirection *= m_myDesc.rotateSpeed;
			m_directionView +=vectorDirection;
			m_directionView.normalize();
			float kinship = m_directionView.dot(m_pointToView);
			updateLaserTorret(m_myDesc.pPlayer);
			if (kinship>=0&& kinship<=1)
			{
				m_timeToRotate = m_elapsedTime + m_constTimeToRotate;
				goingToPos = false;
			} 
		}
		else
		{
			//updateForLoking();
			if (m_elapsedTime > m_timeToRotate)
			{
				m_waitingForNexRotate = false;
			}
		}
	}
	updateForLoking();
	
}

void Boid::rotateToObjetive(Boid* _player)
{
	CD::CDVector2 vectorDirection;
	CD::CDVector2 objetivePos=_player->getPosition();
	vectorDirection = objetivePos-m_position;
	vectorDirection.normalize();
	//vectorDirection -= m_pointViewed;
	//vectorDirection.normalize();
	float kinship = m_directionView.dot(vectorDirection);
	vectorDirection *= m_myDesc.rotateSpeed*2;

	m_directionView += vectorDirection;
	m_directionView.normalize();
	updateForLoking();
	m_timeToRotate = m_elapsedTime + m_constTimeToRotate;
	goingToPos = false;
	updateLaserTorret(m_myDesc.pPlayer);
	
}

void Boid::semirotate()
{
	float x = sin(m_elapsedTime);
	float y = cos(m_elapsedTime);
	m_directionView = { x,y };
	m_directionView.normalize();
	updateForLoking();
}

CD::CDVector2 Boid::instanceBullet()
{
	return CD::CDVector2();
}

void Boid::CalculateImpetuForCollision()
{
	m_impetuForCollision += m_myDesc.seek.impetu;
	m_impetuForCollision += m_myDesc.flee.impetu;
	m_impetuForCollision += m_myDesc.persu.impetu;
	m_impetuForCollision += m_myDesc.evade.impetu;
	m_impetuForCollision += m_myDesc.arrive.impetu;
	m_impetuForCollision += m_myDesc.wander.impetu;
	m_impetuForCollision += m_myDesc.followPath.impetu;
	m_impetuForCollision += m_myDesc.patrol.impetu;
	m_impetuForCollision += m_myDesc.flocking.impetuCohesion;
	m_impetuForCollision += m_myDesc.flocking.impetuDirection;
	m_impetuForCollision += m_myDesc.flocking.impetuSeparation;
	m_impetuForCollision += m_myDesc.followLeader.impetuCohesion;
	m_impetuForCollision += m_myDesc.followLeader.impetuDirection;
	m_impetuForCollision += m_myDesc.followLeader.impetuEvade;
	m_impetuForCollision += m_myDesc.followLeader.impetuFollow;
	m_impetuForCollision += m_myDesc.followLeader.impetuSeparation;
	m_impetuForCollision += 1;
	m_impetuForCollision *= 10;
}

void Boid::calculatePointsToDetecteCollision()
{

	m_frontRightCollisionPointPos = m_directionView*m_myDesc.obstacleEvadeDimentions.sizeFront;
	m_frontRightCollisionPointPos += m_right * m_myDesc.obstacleEvadeDimentions.sizeRight;
	m_frontRightCollisionPointPos += m_position;

	m_frontLeftCollisionPointPos = m_directionView * m_myDesc.obstacleEvadeDimentions.sizeFront;
	m_frontLeftCollisionPointPos += -m_right * m_myDesc.obstacleEvadeDimentions.sizeLeft;
	m_frontLeftCollisionPointPos += m_position;

	m_backRightCollisionPointPos = -m_directionView * m_myDesc.obstacleEvadeDimentions.sizeBack;
	m_backRightCollisionPointPos += m_right * m_myDesc.obstacleEvadeDimentions.sizeRight;
	m_backRightCollisionPointPos += m_position;

	m_backLeftCollisionPointPos = -m_directionView * m_myDesc.obstacleEvadeDimentions.sizeBack;
	m_backLeftCollisionPointPos += -m_right * m_myDesc.obstacleEvadeDimentions.sizeLeft;
	m_backLeftCollisionPointPos += m_position;

	linesForObstacleEvade[0].position = { m_backLeftCollisionPointPos.x,m_backLeftCollisionPointPos.y};
	linesForObstacleEvade[1].position = { m_frontLeftCollisionPointPos.x,m_frontLeftCollisionPointPos.y};
	linesForObstacleEvade[2].position = { m_frontRightCollisionPointPos.x,m_frontRightCollisionPointPos.y};
	linesForObstacleEvade[3].position = { m_backRightCollisionPointPos.x,m_backRightCollisionPointPos.y};
}

void Boid::calculateDimensionToDetecteCollision()
{
	m_sumLeftAndFronVisionObstacle =
		m_myDesc.obstacleEvadeDimentions.sizeFront + m_myDesc.obstacleEvadeDimentions.sizeBack
		+m_myDesc.obstacleEvadeDimentions.sizeLeft + m_myDesc.obstacleEvadeDimentions.sizeRight;
	m_sumLeftAndFronVisionObstacle *= 2;
	m_anche= m_myDesc.obstacleEvadeDimentions.sizeLeft + m_myDesc.obstacleEvadeDimentions.sizeRight;
	m_large = m_myDesc.obstacleEvadeDimentions.sizeFront + m_myDesc.obstacleEvadeDimentions.sizeBack;

	m_hipotenuse = sqrt((m_anche*m_anche+m_large*m_large));
}

bool Boid::detectedCollision(Obstacle* _obstacle)
{
	float ObstacleRatio = _obstacle->getRatio();
	CD::CDVector2 obstaclePosition = _obstacle->getPosition();
	CD::CDVector2 hipotenusa1= m_frontLeftCollisionPointPos;
	CD::CDVector2 hipotenusa2= m_backRightCollisionPointPos;
	CD::CDVector2 collisionPoint = m_position- obstaclePosition;
	collisionPoint.normalize();
	collisionPoint *= ObstacleRatio;
	collisionPoint += obstaclePosition;
	//frontRightToObstacle[0].position = { m_frontLeftCollisionPointPos.x,m_frontLeftCollisionPointPos.y };
	//frontRightToObstacle[1].position = { collisionPoint.x,collisionPoint.y };
	//
	//backLeftToObstacle[0].position = { m_backRightCollisionPointPos.x,m_backRightCollisionPointPos.y };
	//backLeftToObstacle[1].position = { collisionPoint.x,collisionPoint.y };
	hipotenusa1 -= collisionPoint;
	hipotenusa2 -= collisionPoint;
	float sumOfHipotenusas =
		hipotenusa1.length()
		+ hipotenusa2.length();
	CD::CDVector2 v1 = m_backRightCollisionPointPos - m_frontRightCollisionPointPos;
	CD::CDVector2 v2 = m_backRightCollisionPointPos - m_backLeftCollisionPointPos;
	CD::CDVector2 v3 = m_frontLeftCollisionPointPos - m_frontRightCollisionPointPos;
	CD::CDVector2 v4 = m_frontLeftCollisionPointPos - m_backLeftCollisionPointPos;
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

float Boid::calculateAngle(const CDVector2& _vec)
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
		}if (_vec.y > 0 && _vec.x > 0)
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

void Boid::initLifeBars()
{
	sf::Color barColor = sf::Color::Green;
	sf::Vector2f size = {5,16};
	lifeBars[0].setPosition(1, 1);
	lifeBars[0].setFillColor(barColor);
	lifeBars[0].setSize(size);
	lifeBars[1].setPosition(9, 1);
	lifeBars[1].setFillColor(barColor);
	lifeBars[1].setSize(size);;
	lifeBars[2].setPosition(17, 1);
	lifeBars[2].setFillColor(barColor);
	lifeBars[2].setSize(size);
	lifeBars[3].setPosition(25, 1);
	lifeBars[3].setFillColor(barColor);
	lifeBars[3].setSize(size);
	lifeBars[4].setPosition(33, 1);
	lifeBars[4].setFillColor(barColor);
	lifeBars[4].setSize(size);
	lifeBars[5].setPosition(41, 1);
	lifeBars[5].setFillColor(barColor);
	lifeBars[5].setSize(size);
}

void Boid::updateLaserTorret(Boid*_player)
{

	float angle = calculateAngle(m_directionView.getnormalize());
	angle *= 180 / 3.1415f;
	m_LaserTooret.setRotation(-angle);
	CDVector2 pos = m_position + (m_directionView * m_myDesc.ratio);
	m_LaserTooret.setPosition(pos.x, pos.y);
	CDVector2 playerPos =  _player->getPosition();
	CDVector2 objetivePos = m_position - playerPos;
	objetivePos.normalize();
	objetivePos *= _player->getRatio();
	objetivePos += playerPos;
	objetivePos = objetivePos-m_position ;
	CDVector2 front = m_directionView * m_myDesc.ratioToLooking;
	float kinship = objetivePos.dot(front);
	if (kinship<0)
	{
		return;
	}
	CDVector2 vectorProyection = playerPos - m_position;
	float proyection = vectorProyection.length();
	proyection /= front.length();
	if (proyection>1)
	{
		proyection = 1;
	}
	CD::CDVector2 nearPoint = (front * proyection) + m_position;
	CDVector2 boidCollisionPoint = nearPoint - playerPos;
	if (boidCollisionPoint.length()< _player->getRatio())
	{

		_player->takeDamageToPlayer();
		return;
	}
	boidCollisionPoint.normalize();
	boidCollisionPoint *= _player->getRatio();
	boidCollisionPoint += playerPos;
	nearPoint -= boidCollisionPoint;
	float length = nearPoint.length();

	if (length- m_ratioLaserTorret <= m_ratioLaserTorret)
	{
		_player->takeDamageToPlayer();

	}
}

float Boid::calculateProyectionOfVector(const CDVector2& _mainVector, const CDVector2& _VectorToProyect)
{
	float kiship = _mainVector.dot(_VectorToProyect);
	if (kiship<0)
	{
		return 0;
	}
	float proyection = _VectorToProyect.length() / _mainVector.length();
	return proyection;
}
