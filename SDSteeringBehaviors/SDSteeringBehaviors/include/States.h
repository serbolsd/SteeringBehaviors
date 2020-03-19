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
	EXPLOTINGSTATE
};
class Boid;
class State
{
public:
	State();
	virtual ~State();
	virtual void onEnter() {};
	virtual ENUMSTATES onUpdate(Boid* _boid) { return ENUMSTATES::UNKNOWSTATE; };
	virtual void onExit() {};
private:

};

class StateIdle :public State
{
public:
	StateIdle ();
	~StateIdle ();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:
	

};

class Statechasing :public State
{
public:
	Statechasing();
	~Statechasing();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:

};

class StateWalking :public State
{
public:
	StateWalking();
	~StateWalking();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:

};

class StateShooting : public  State
{
public:
	StateShooting();
	~StateShooting();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:

};

class StateExploding :public State
{
public:
	StateExploding();
	~StateExploding();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:

};

class StateLooking :public State
{
public:
	StateLooking();
	~StateLooking();
	void onEnter() override;
	ENUMSTATES onUpdate(Boid* _boid) override;
	void onExit() override;
private:

};