#include "States.h"
#include "Boid.h"

StateLooking::StateLooking()
{
}

StateLooking::~StateLooking()
{
}

void StateLooking::onEnter(Boid* _boid)
{
}

ENUMSTATES StateLooking::onUpdate(Boid* _boid)
{
	switch (_boid->getTypeBoid())
	{
	case TYPEBOID::TANK:
		if (_boid->lookingForPlayer(_boid->m_myDesc.pPlayer, _boid->m_myDesc.AngleToLookingInDegrees, _boid->m_myDesc.ratioToLooking))
			return ENUMSTATES::CHASINGSTATE;
		break;
	case TYPEBOID::CAMERA:
		break;
	case TYPEBOID::TORRET:
		break;
	case TYPEBOID::SCIENTIFIC:
		break;
	default:
		break;
	}
	//if (_boid->IsWatchingPlayer)
	//{
	//	return ENUMSTATES::SHOOTINGSTATE;
	//}
	return ENUMSTATES::LOOKINGSTATE;
}

void StateLooking::onExit(Boid* _boid)
{
}