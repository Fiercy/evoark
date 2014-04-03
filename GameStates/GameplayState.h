#pragma once
#include "IGameState.h"
#include "LevelStates\ILevelState.h"
//#include "../Entities/Ships/Player.h"
//#include "GameState.h"
#include "../Message System/MessageID.h"
#include <vector>

enum class Level { Tutorial, Gen1, Gen2, Gen3, Waves, Final, LoadedLevel, TestStatic, TestGen };
struct playerData
{
	unsigned int level;
	unsigned int exp;
	unsigned int expRequired;
	unsigned int perks;
	unsigned int laserLevel;
	unsigned int missileLevel;
	unsigned int wellLevel;
	unsigned int pushLevel;
	unsigned int warpLevel;
};

struct waveData
{
	unsigned int alliesSaved;
	unsigned int enemiesKilled;
};

struct EntityData
{
	EntityType type;
	unsigned int hull;
	unsigned int shield;
	SGD::Point position;
	bool coord;
};

struct ModularEntityData
{
	EntityType type;
	SGD::Point position;
	std::vector<EntityData> modules;
};

struct Flock
{
	EntityType type;
	SGD::Point home;
	bool backup;
	std::vector<EntityData> members;
};

struct ModularFlock
{
	EntityType type;
	SGD::Point home;
	bool backup;
	std::vector<ModularEntityData> members;
};

struct CollidableData
{
	EntityType type;
	MessageID ID;
	SGD::Point position;
	SGD::Size size;
};

struct worldData
{
	bool saved = false;
	std::vector<EntityData> entities;
	EntityData boss;
	std::vector<Flock> flocks;
	std::vector<ModularFlock> modFlocks;
	std::vector<CollidableData> collidables;
};

struct saveData
{
	unsigned int profile;
	playerData playerStat;
	waveData waveStat;
	Level currLevel = Level::Gen1;
	worldData world;
};

class CGameplayState : public IGameState
{
	saveData save;
	CGameplayState();
	~CGameplayState();
public:
	static CGameplayState* GetInstance();
	virtual bool Input() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Enter() override;

	void SaveProfile();
	void LoadProfile();

	Level GetLevel() {return save.currLevel;}
	void SetLevel(Level l) {save.currLevel = l;}
	//friend ILevelState;

	unsigned int GetProfile() {return save.profile;}
	void SetProfile(unsigned int profile) {save.profile = profile;}
};