#pragma once
#include "CDVectors.h"
#include "SFML/Graphics.hpp"
#include <vector>
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
	void Init(BoidDescriptor _Desc);
	void Update();
	void Render(sf::RenderWindow &_wind);
	void Delete();
	CD::CDVector2 getPosition() { return m_Position; };
	CD::CDVector2 getDirection() { return m_Direction; };
	CD::CDVector2 getDirectionView() { return m_DirectionView; };
	float getDistanceToView() { return myDesc.obstacleEvadeDimentions.sizeFront; };
	float getSpeed() { return m_Speed; };
	float getRatio() { return myDesc.ratio; };
	TYPEBOID getTypeBoid() { return mytype; };

	static CD::CDVector2 seek(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 flee(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu);
	static CD::CDVector2 fleeRatio(CD::CDVector2 PosA, CD::CDVector2 PosB,float Impetu,float ratio);
	static CD::CDVector2 arrive(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB,float Impetu,float ratio, float masa);
	static CD::CDVector2 persu(CD::CDVector2 PosA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 evade(CD::CDVector2 PosA, CD::CDVector2 DirA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB,float TimeProyection,float Impetu);
	static CD::CDVector2 wanderRandom(CD::CDVector2 PosA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu);
	static CD::CDVector2 wanderTime(CD::CDVector2 PosA,CD::CDVector2 DirA,CD::CDVector2 LimitsX, CD::CDVector2 LimitsY,float impetu,float &timeElapsed,float TimeToNextPoint);
	static CD::CDVector2 wander(CD::CDVector2 PosA,CD::CDVector2 DirA,float impetu,float distToProyection,float ratio,float angle);
	static CD::CDVector2 FollowPath(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio);
	static CD::CDVector2 PatrolCircuit(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay);
	static CD::CDVector2 PatrolInverted(CD::CDVector2 PosA, std::vector <CD::CDVector2> Points, float impetu, int& indexPath, float Ratio, float& timeElapsed,float timeToStay,bool &bReturn);
	static CD::CDVector2 Direction(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
	static CD::CDVector2 Cohesion(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetu);
	static CD::CDVector2 Separation(Boid* A, std::vector<Boid*>* Boids, float impetu);
	static CD::CDVector2 flocking(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetuDiretion, float impetuCohesion, float impetuSeparation);
	static CD::CDVector2 FollowTheLeader(Boid* A, std::vector<Boid*>* Boids, float ratioVision, float impetuFollow, float impetuEvade, float impetuDiretion, float impetuCohesion, float impetuSeparation, Boid* leader, float distToLeader);
	static CD::CDVector2 obstacleCollision(Boid* A, std::vector <Obstacle*>* ptr_obstacles,float Impetu);
	static CD::CDVector2 obstacleEvade(Boid* A, std::vector <Obstacle*>* ptr_obstacles,float Impetu);
private:
	static CD::CDVector2 Inercia(CD::CDVector2 DirA, CD::CDVector2 newDir,float masa);
	static CD::CDVector2 truncar(CD::CDVector2 Dir,float speed);
	void CalculateImpetuForCollision();
	void calculatePointsToDetecteCollision();
	void calculateDimensionToDetecteCollision();
	bool detectedCollision(Obstacle* _obstacle);

	CD::CDVector2 m_Position;
	CD::CDVector2 m_Direction;
	CD::CDVector2 m_DirectionView;
	CD::CDVector2 Right;
	float m_Speed=0;
	sf::CircleShape shape;
	BoidDescriptor myDesc;
	float ElapsedTime=0;
	float impetuForCollision = 0;
	CD::CDVector2 frontRightCollisionPointPos;
	CD::CDVector2 frontLeftCollisionPointPos;
	CD::CDVector2 backRightCollisionPointPos;
	CD::CDVector2 backLeftCollisionPointPos;
	float sumLeftAndFronVisionObstacle = 0;
	float anche = 0;
	float large = 0;
	float hipotenuse = 0;
	bool thereAreObstacles = false;
	sf::VertexArray linesForObstacleEvade;
	sf::VertexArray backLeftToObstacle;
	sf::VertexArray frontRightToObstacle;
	TYPEBOID mytype = TYPEBOID::UNKNOWBOID;
};
