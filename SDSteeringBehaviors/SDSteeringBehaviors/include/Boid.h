#pragma once
#include "CDVectors.h"
#include "SFML/Graphics.hpp"
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
	unknowWander = 0,
	WanderRandom,
	wanderTime,
	WanderVision
};
struct WanderDescriptor
{
	TypeWander type= unknowWander;
	CD::CDVector2 limitsX = { 0,0 };// .x is the minimun .y de maximun
	CD::CDVector2 limitsY = { 0,0 };// .x is the minimun .y de maximun
	float impetu=0;
	float timeToNextPoint=0;
	float ratio=0;
	float openingAngleInDegrees = 0;
	float DistoToPointProyection = 0;

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

	static CD::CDVector2 seek(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 flee(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 fleeRatio(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu,float ratio);
	static CD::CDVector2 arrive(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu,float ratio);
	static CD::CDVector2 persu(CD::CDVector2 PosA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 evade(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 wanderRandom(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu);
	static CD::CDVector2 wanderTime(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu,float &timeElapsed,float TimeToNextPoint);
	static CD::CDVector2 wanderTime(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu,float distToPoint,float ratio,float angle);
private:
	CD::CDVector2 m_Position;
	CD::CDVector2 m_Direction;
	float m_Speed=0;
	sf::CircleShape shape;
	BoidDescriptor myDesc;

};
