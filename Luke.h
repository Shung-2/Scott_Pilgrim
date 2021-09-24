#pragma once
#include "Enemy.h"
#include "EnemyState.h"

class Luke : public Enemy
{
private:

public:
	Luke();
	~Luke();

	virtual void Init();
};