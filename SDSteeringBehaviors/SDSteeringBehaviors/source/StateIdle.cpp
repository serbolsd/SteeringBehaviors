#include "States.h"
#include "Boid.h"

StateIdle::StateIdle()
{
}

StateIdle::~StateIdle()
{
}

void StateIdle::onEnter(Boid* _boid)
{
}

ENUMSTATES StateIdle::onUpdate(Boid* _boid)
{
    switch (_boid->getTypeBoid())
    {
    case TYPEBOID::UNKNOWBOID:
        break;
    case TYPEBOID::PLAYER:
        if (_boid->getDirection() != CD::CDVector2(0, 0))
        {
            return ENUMSTATES::WALKINGSTATE;
        }
        break;
    case TYPEBOID::TANK:
        //if (Watch player)
        //{
        //   return ENUMSTATES::CHASINGSTATE;
        //}
        break;
    case TYPEBOID::CAMERA:
        //   return ENUMSTATES::LOOKINGSTATE;
        break;
    case TYPEBOID::TORRET:
        //   return ENUMSTATES::LOOKINGSTATE;
        break;
    case TYPEBOID::SCIENTIFIC:
        break;
    default:
        break;
    }
    return ENUMSTATES::IDLESTATE;
}

void StateIdle::onExit(Boid* _boid)
{
}