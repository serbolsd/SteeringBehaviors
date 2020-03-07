#include "States.h"
#include "Boid.h"

StateIdle::StateIdle()
{
}

StateIdle::~StateIdle()
{
}

State* StateIdle::update(Boid* _boid)
{
    prepare();
	switch (_boid->getTypeBoid())
	{
    case TYPEBOID::UNKNOWBOID:
        return new StateIdle();
        break;
    case TYPEBOID::PLAYER:
        if (_boid->getDirection()!=CD::CDVector2(0,0))
        {
            return new StateWalking();
        }
        break;
    case TYPEBOID::TANK:
        //if (Watch player)
        //{
        //   return new Statechasing();
        //}
        break;
    case TYPEBOID::CAMERA:
        //   return new StateLooking();
        break;
    case TYPEBOID::TORRET:
        //   return new StateLooking();
        break;
    case TYPEBOID::SCIENTIFIC:
        break;
    default:
        break;  
	}
    return new StateIdle();
}
