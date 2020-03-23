#pragma once
#include "CDVectors.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "States.h"
#include <StateMachine.h>
class Obstacle;
class Boid;
enum class TYPEBOID
{
	UNKNOWBOID=0,
	PLAYER,
	TANK,
	CAMERA,
	TORRET,
	SCIENTIFIC
};
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
enum class TypeWander
{
	unknowWanderType = 0,
	WanderTypeRandom,
	wanderTypeTime,
	WanderTypeVision
};
struct WanderDescriptor
{
	TypeWander type= TypeWander::unknowWanderType;
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
	std::vector <CD::CDVector2> *Points=nullptr;
	int IndexPoint=0;
	float ratio=0;
	float impetu=0;

};
enum class TypePatrol
{
	unknowPatrolType = 0,
	PatrolTypeCircuit,
	PatrolTypeInverted
};
struct PatrolDescriptor
{
	TypePatrol type = TypePatrol::unknowPatrolType;
	std::vector <CD::CDVector2>* Points=nullptr;
	float impetu=0;
	int indexPath=0; 
	float Ratio=4; 
	float timeToStay=0;
	bool bReturn=false;
};
struct flockingDescriptor
{
	std::vector<Boid*>* Boids = nullptr;
	float ratioVision = 0;
	float impetuDirection = 0;
	float impetuCohesion = 0;
	float impetuSeparation = 0;
};
struct followTheLeaderDescriptor
{
	Boid* Leader=nullptr;
	float distToLeader=0;
	float impetuFollow = 0;
	float impetuEvade = 0;
	float impetuDirection = 0;
	float impetuCohesion = 0;
	float impetuSeparation = 0;
	std::vector<Boid*>* Boids = nullptr;
	float ratioVision = 0;
	float impetu = 0;
};
struct obstacleEvadeDescriptor
{
	float sizeLeft = 0.0f;//since the center of boid
	float sizeRight = 0.0f;//since the center of boid
	float sizeBack = 0.0f;//since the center of boid
	float sizeFront = 0.0f;//since the center of boid
	float impetu = 0.0f;
};
struct BoidDescriptor
{
	CD::CDVector2 Position = CD::CDVector2(0, 0);
	CD::CDVector2 Direction= CD::CDVector2(0,0);
	CD::CDVector2 DirectionView= CD::CDVector2(1,0);
	float Speed=0;
	float ratio=4;
	float masa=1;
	SeekDescriptor seek;
	FleeDescriptor flee;
	ArriveDescriptor arrive;
	PersuDescriptor persu;
	EvadeDescriptor evade;
	WanderDescriptor wander;
	FollowPathDescriptor followPath;
	PatrolDescriptor patrol;
	flockingDescriptor flocking;
	followTheLeaderDescriptor followLeader;
	obstacleEvadeDescriptor obstacleEvadeDimentions;
	sf::Color shapeColor = {130,0,255,255};
	float *globalTime=nullptr;
	std::vector <Obstacle*> *ptr_obstacles=nullptr;
	TYPEBOID BoidType = TYPEBOID::UNKNOWBOID;
};

class Boid
{
public:
	Boid();
	~Boid();
	void Init(const BoidDescriptor& _Desc);
	void Update();
	void Render(sf::RenderWindow &_wind);
	void Delete();
	CD::CDVector2 getPosition() { return m_position; };
	CD::CDVector2 getDirection() { return m_direction; };
	CD::CDVector2 getDirectionView() { return m_directionView; };
	float getDistanceToView() { return m_myDesc.obstacleEvadeDimentions.sizeFront; };
	float getSpeed() { return m_speed; };
	float getRatio() { return m_myDesc.ratio; };
	TYPEBOID getTypeBoid() { return m_mytype; };
	const ENUMSTATES &getEnumCurrentState() { return m_eMyCurrentState; };
	const ENUMSTATES &getEnumPastState() { return m_eMyPastState; };
	void setState(State* _newState) { m_pMyState = _newState; };
	State* getState() { return m_pMyState; };

	CD::CDVector2 seek(CD::CDVector2 PosB,float impetu);
	CD::CDVector2 flee( CD::CDVector2 PosB,float impetu);
	CD::CDVector2 fleeRatio(CD::CDVector2 PosB, float impetu, float ratio);
	CD::CDVector2 arrive(CD::CDVector2 PosB, float impetu, float ratio);
	CD::CDVector2 persu(CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection, float impetu);
	CD::CDVector2 evade(CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection, float impetu);
	CD::CDVector2 wanderRandom(CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu);
	CD::CDVector2 wanderTime(CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu,float TimeToNextPoint);
	CD::CDVector2 wander(float impetu,float distToProyection,float ratio,float angle);
	CD::CDVector2 FollowPath( std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio);
	CD::CDVector2 PatrolCircuit(std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay);
	CD::CDVector2 PatrolInverted(std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay,bool &bReturn);
	CD::CDVector2 Direction(std::vector<Boid*>* Boids, float ratioVision, float impetu);
	CD::CDVector2 Cohesion(std::vector<Boid*>* Boids, float ratioVision, float impetu);
	CD::CDVector2 Separation(std::vector<Boid*>* Boids, float impetu);
	CD::CDVector2 flocking(std::vector<Boid*>* Boids, float ratioVision, float impetuDiretion, float impetuCohesion, float impetuSeparation);
	CD::CDVector2 FollowTheLeader(std::vector<Boid*>* Boids, float ratioVision, float impetuFollow, float impetuEvade, float impetuDiretion, float impetuCohesion, float impetuSeparation, Boid* leader, float distToLeader);
	CD::CDVector2 obstacleCollision(std::vector <Obstacle*>* ptr_obstacles,float Impetu);
	CD::CDVector2 obstacleEvade(std::vector <Obstacle*>* ptr_obstacles,float Impetu);
private:
	CD::CDVector2 Inercia(CD::CDVector2 newDir);
	CD::CDVector2 truncar(CD::CDVector2 Dir,float speed);
	void CalculateImpetuForCollision();
	void calculatePointsToDetecteCollision();
	void calculateDimensionToDetecteCollision();
	bool detectedCollision(Obstacle* _obstacle);

	CD::CDVector2 m_position;
	CD::CDVector2 m_direction;
	CD::CDVector2 m_directionView;
	CD::CDVector2 m_right;
	float m_speed=0;
	sf::CircleShape m_shape;
	BoidDescriptor m_myDesc;

	float m_elapsedTime=0;
	float m_impetuForCollision = 0;
	CD::CDVector2 m_frontRightCollisionPointPos;
	CD::CDVector2 m_frontLeftCollisionPointPos;
	CD::CDVector2 m_backRightCollisionPointPos;
	CD::CDVector2 m_backLeftCollisionPointPos;
	float m_sumLeftAndFronVisionObstacle = 0;
	float m_anche = 0;
	float m_large = 0;
	float m_hipotenuse = 0;
	bool m_thereAreObstacles = false;
	sf::VertexArray m_linesForObstacleEvade;
	sf::VertexArray m_backLeftToObstacle;
	sf::VertexArray m_frontRightToObstacle;

	TYPEBOID m_mytype = TYPEBOID::UNKNOWBOID;
	State* m_pMyState = nullptr;
	StateMachine* m_pStateMachine=nullptr;
	ENUMSTATES m_eMyCurrentState = ENUMSTATES::IDLESTATE;
	ENUMSTATES m_eMyPastState = ENUMSTATES::UNKNOWSTATE;
};
