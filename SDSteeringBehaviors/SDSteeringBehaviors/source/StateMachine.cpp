#include <StateMachine.h>
#include <Boid.h>
StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::init()
{
	m_pIdleState = new StateIdle();
	m_pWalkingState = new StateWalking();
	m_pChasingState = new Statechasing();
	m_pLookingState = new StateLooking();
	m_pShootingState = new StateShooting();
	m_pExplotingState = new StateExploding();
	m_pDeadState = new StateDead();
}

void StateMachine::updateState(Boid& _boid)
{
	ENUMSTATES currentState = _boid.getEnumCurrentState();
	ENUMSTATES pastState = _boid.getEnumPastState();
	bool ChangingState = false;
	if (currentState != pastState)
	{
		pastState = currentState;
		ChangingState = true;
		_boid.getState()->onExit(&_boid);
	}
	switch (_boid.getEnumCurrentState())
	{
	case ENUMSTATES::UNKNOWSTATE:
		break;
	case ENUMSTATES::IDLESTATE:
		_boid.setState(m_pIdleState);
		break;
	case ENUMSTATES::CHASINGSTATE:
		_boid.setState(m_pChasingState);
		break;
	case ENUMSTATES::LOOKINGSTATE:
		_boid.setState(m_pLookingState);
		break;
	case ENUMSTATES::SHOOTINGSTATE:
		_boid.setState(m_pShootingState);
		break;
	case ENUMSTATES::WALKINGSTATE:
		_boid.setState(m_pWalkingState);
		break;
	case ENUMSTATES::EXPLOTINGSTATE:
		_boid.setState(m_pExplotingState);
		break;
	case ENUMSTATES::DEADSTATE:
		_boid.setState(m_pDeadState);
		break;
	default:
		break;
	}
	if (ChangingState)
	{
		_boid.getState()->onEnter(&_boid);
	}
	
}

void StateMachine::onDelete()
{
	if (m_pIdleState != nullptr)
	{
		delete m_pIdleState;
	}
	if (m_pWalkingState != nullptr)
	{
		delete m_pWalkingState;
	}
	if (m_pChasingState != nullptr)
	{
		delete m_pChasingState;
	}
	if (m_pLookingState != nullptr)
	{
		delete m_pLookingState;
	}
	if (m_pShootingState != nullptr)
	{
		delete m_pShootingState;
	}
	if (m_pExplotingState != nullptr)
	{
		delete m_pExplotingState;
	}
	if (m_pDeadState!=nullptr)
	{
		delete m_pDeadState;
	}
}
