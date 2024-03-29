#pragma once
#include "IGameState.h"
#include "../Menu.h"
class CPauseState :
	public IGameState
{
	enum menuReturn { Continue, ForceCheckpoint, ForceSave, Upgrades, Options, MainMenu, count };
	CMenu* menu;

	CPauseState();
	virtual ~CPauseState();
public:

	static CPauseState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

