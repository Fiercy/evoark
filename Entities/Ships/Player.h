#pragma once
#include "Ship.h"
struct playerData;
class CShield;
class CEmitter;
class CPlayer :
	public CShip
{
	int shield;
	int maxShield;
	int shieldRegen;

	int exp;
	int expRequired;
	int level;
	int perks = 0;
	int laserLevel = 0;
	int missileLevel = 0;
	int wellLevel = 0;
	int pushLevel = 0;
	int warpLevel = 0;

	float shieldTimer;
	float laserTimer;
	float missileTimer;
	float wellTimer = 0;
	float pushTimer = 0;
	float warpTimer = 0;

	float shieldDelay;
	float laserDelay;
	float missileDelay;
	float wellDelay = 6.0f;
	float pushDelay = 6.0f;
	float warpDelay = 3.0f;

	float warpSpeed;
	float warpDuration = 1;

	bool arrowsOn = false;

	float damaged = 0.f;

	SGD::HTexture wellIcon = SGD::INVALID_HANDLE;
	SGD::HTexture pushIcon = SGD::INVALID_HANDLE;
	SGD::HTexture warpIcon = SGD::INVALID_HANDLE;

	CShield* m_shield;
	CEmitter* m_Engine;

	SGD::Point enginePos;
	// tutorial
	bool tutorialWaitForInput[6];
	bool tutorialTriggerHit[6];

	// level up graphic
	float levelUpTimer = 0.f;

public:
	CPlayer();
	virtual ~CPlayer();

	int GetType() override {return (int)EntityType::Player;}
	void Update(float dt) override;
	void AddGravity(SGD::Vector grav) override;
	void TakeDamage(int damage, bool collision = false) override;
	void SetShield(CShield* p) { m_shield = p; }
	void SetShieldValue(int value) {shield = value;}

	int GetShield() { return shield; }
	int GetMaxShield() { return maxShield; }
	int GetExp() { return this->exp; }
	int GetReqExp() { return expRequired; }
	int GetLevel() { return level; }
	int GetPerks() { return perks; }
	int GetLaserLevel() { return laserLevel; }
	int GetMissileLevel() { return missileLevel; }
	int GetWellLevel() { return wellLevel; }
	int GetPushLevel() { return pushLevel; }
	int GetWarpLevel() { return warpLevel; }
	float GetWellDelay() { return wellDelay; }
	float GetPushDelay() { return pushDelay; }
	float GetWarpDelay() { return warpDelay; }
	float GetWellTimer() { return wellTimer; }
	float GetPushTimer() { return pushTimer; }
	float GetWarpTimer() { return warpTimer; }
	bool  GetArrowsOn() { return arrowsOn; }
	SGD::Point GetEnginePos() { return enginePos; }

	void AddExp(int _exp);
	void LaserLevelUp();
	void MissileLevelUp() { missileLevel++; }
	void WellLevelUp() { wellLevel++; }
	void PushLevelUp() { pushLevel++; }
	void WarpLevelUp();
	void RemovePerk() { perks--; }

	// for tutorial
	int GetTutorialPause();
	void SetTutorialPause(int i) { tutorialWaitForInput[i] = !tutorialWaitForInput[i]; }

	// get textures for icons
	SGD::HTexture GetWellIcon() { return wellIcon; }
	SGD::HTexture GetPushIcon() { return pushIcon; }
	SGD::HTexture GetWarpIcon() { return warpIcon; }

	//void HandleCollision(IEntity* other) override;
	//Coment out later:
	void Render() override;

	void CreateLaser();
	void CreateMissile();
	void CreateWell();
	void CreateWellController();
	void CreatePush();
	void Warp();

	void HandleCollision(IEntity* other) override;

	void SetStats(playerData& data);
};

