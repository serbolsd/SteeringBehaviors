#pragma once
#include <States.h>
class Boid;
class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void init();
	void updateState(Boid& _boid);
	void onDelete();
private:
	State* m_pIdleState = nullptr;
	State* m_pWalkingState = nullptr;
	State* m_pChasingState = nullptr;
	State* m_pLookingState = nullptr;
	State* m_pShootingState = nullptr;
	State* m_pExplotingState=nullptr;
};
