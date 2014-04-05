#pragma once
#include "Trigger.h"
#include "../IEntity.h"

enum class triggerID { tutMovement, tutLasers, tutMissiles, tutWarp, tutWell, tutPush, tutCoordinator, tutHuman, tutBoss, };

class EventTrigger : public Trigger
{
	int triggerType = -1;
	bool colliding = false;

public:
	EventTrigger(){}
	~EventTrigger(){}

	void Render();

	void SetType(int _type) { triggerType = _type; }

	void HandleCollision(IEntity* other);
};
