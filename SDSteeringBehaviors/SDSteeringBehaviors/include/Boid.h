#pragma once
#include "CDVectors.h"
#include "SFML/Graphics.hpp"
#include <vector>
class Boid;
struct SeekDescriptor
{
	CD::CDVector2* objetive=nullptr;
	float impetu = 0;
};
struct FleeDescriptor
{
	CD::CDVector2* objetive = nullptr;
	float impetu = 0;
	float ratio = 0;
};
struct ArriveDescriptor
{
	CD::CDVector2* objetive = nullptr;
	float impetu = 0;
	float ratio = 0;
};
struct PersuDescriptor
{
	Boid* objetive = nullptr;
	float impetu = 0;
	float timeProyection=0;
};
struct EvadeDescriptor
{
	Boid* objetive = nullptr;
	float impetu = 0;
	float timeProyection = 0;
};
enum TypeWander
{
	unknowWanderType = 0,
	WanderTypeRandom,
	wanderTypeTime,
	WanderTypeVision
};
struct WanderDescriptor
{
	TypeWander type= unknowWanderType;
	CD::CDVector2 limitsX = { 0,0 };// .x is the minimun .y de maximun
	CD::CDVector2 limitsY = { 0,0 };// .x is the minimun .y de maximun
	float impetu=0;
	float timeToNextPoint=0;
	float ratio=0;
	float openingAngleInDegrees = 0;
	float DistoToPointProyection = 0;
};
struct FollowPathDescriptor
{
	std::vector <CD::CDVector2> *Points;
	int IndexPoint=0;
	float ratio=0;
	float impetu;

};
enum TypePatrol
{
	unknowPatrolType = 0,
	PatrolTypeCircuit,
	PatrolTypeInverted
};
struct PatrolDescriptor
{
	TypePatrol type = unknowPatrolType;
	std::vector <CD::CDVector2>* Points=nullptr;
	float impetu=0;
	int indexPath=0; 
	float Ratio=4; 
	float timeToStay=0;
	bool bReturn=false;
};
struct flockingDescriptor
{

};
struct BoidDescriptor
{
	CD::CDVector2 m_Position;
	CD::CDVector2 m_Direction;
	float m_Speed=0;
	float ratio=4;
	SeekDescriptor seek;
	FleeDescriptor flee;
	ArriveDescriptor arrive;
	PersuDescriptor persu;
	EvadeDescriptor evade;
	WanderDescriptor wander;
	FollowPathDescriptor followPath;
	PatrolDescriptor patrol;
	sf::Color shapeColor = {130,0,255,255};
	float *globalTime=nullptr;
};

class Boid
{
public:
	Boid();
	~Boid();
	void Init(BoidDescriptor _Desc);
	void Update();
	void Render(sf::RenderWindow &_wind);
	void Delete();
	CD::CDVector2 getPosition() { return m_Position; };
	CD::CDVector2 getDirection() { return m_Direction; };
	float getSpeed() { return m_Speed; };
	float getRatio() { return myDesc.ratio; };

	static CD::CDVector2 seek(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 flee(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 fleeRatio(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu,float ratio);
	static CD::CDVector2 arrive(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu,float ratio);
	static CD::CDVector2 persu(CD::CDVector2 PosA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 evade(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 wanderRandom(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu);
	static CD::CDVector2 wanderTime(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu,float &timeElapsed,float TimeToNextPoint);
	static CD::CDVector2 wander(CD::CDVector2 PosA,CD::CDVector2 DirA,float impetu,float distToProyection,float ratio,float angle);
	static CD::CDVector2 FollowPath(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio);
	static CD::CDVector2 PatrolCircuit(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay);
	static CD::CDVector2 PatrolInverted(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay,bool &bReturn);
	static CD::CDVector2 Direction(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
	static CD::CDVector2 Cohesion(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
	static CD::CDVector2 Separation(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
	static CD::CDVector2 flocking(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
private:
	CD::CDVector2 m_Position;
	CD::CDVector2 m_Direction;
	float m_Speed=0;
	sf::CircleShape shape;
	BoidDescriptor myDesc;
	float ElapsedTime=0;
};
