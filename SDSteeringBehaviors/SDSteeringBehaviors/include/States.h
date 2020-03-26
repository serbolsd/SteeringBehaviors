#pragma once
#include "CDVectors.h"
enum class ENUMSTATES
{
	UNKNOWSTATE=0,
	IDLESTATE,
	CHASINGSTATE,
	LOOKINGSTATE,
	SHOOTINGSTATE,
	WALKINGSTATE,
	EXPLOTINGSTATE,
	DEADSTATE
};
class Boid;
class State
{
public:
	State();
	virtual ~State();
	virtual void onEnter(Boid* _boid) {};
	virtual ENUMSTATES onUpdate(Boid* _boid) { return ENUMSTATES::UNKNOWSTATE; };
	virtual void onExit(Boid* _boid) {};
private:

};

class StateIdle :public State
{
public:
	StateIdle ();
	~StateIdle ();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:
	

};

class Statechasing :public State
{
public:
	Statechasing();
	~Statechasing();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};

class StateWalking :public State
{
public:
	StateWalking();
	~StateWalking();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};

class StateShooting : public  State
{
public:
	StateShooting();
	~StateShooting();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};

class StateExploding :public State
{
public:
	StateExploding();
	~StateExploding();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};

class StateLooking :public State
{
public:
	StateLooking();
	~StateLooking();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};

class StateDead :public State
{
public:
	StateDead();
	~StateDead();
	void onEnter(Boid* _boid) override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit(Boid* _boid) override;
private:

};