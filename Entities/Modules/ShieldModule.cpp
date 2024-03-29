//
#include "ShieldModule.h"
#include "../Ships/Enemies/Coral.h"
CShieldModule::CShieldModule()
{
	hullMax = 200;
	hull = hullMax;

	cooldown = 4;
	shield = 25;
	shieldMax = 25;
}


CShieldModule::~CShieldModule()
{
}

void CShieldModule::Update(float dt)
{


	CModule::Update(dt);
	if (timer >= cooldown)
	{
		shield += int(regen * dt);
		if (shield > shieldMax)
			shield = shieldMax;
	}


}

int CShieldModule::RequestShield(int damage)
{
	int ret;
	if (damage > shield)
		ret = shield;
	else
		ret = damage;
	shield -= damage;
	if (shield < 0)
		shield = 0;
	timer = 0;
	return ret;
}