#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	renderer = new Renderer();
	animator = new Animator();
	zOrder = new ZOrder();
	shadow = new Shadow();
	enemyinfo = new EnemyInfo();
	enemyAI = new EnemyAI();

	AddComponent(zOrder);
	zOrder->Init();

	AddComponent(shadow);
	shadow->Init();

	AddComponent(renderer);
	renderer->Init();

	AddComponent(animator);
	animator->Init();

	AddComponent(enemyinfo);
	enemyinfo->Init();

	AddComponent(enemyAI);
	enemyAI->Init();	
}

Enemy::~Enemy()
{
	SAFE_DELETE(renderer);
	SAFE_DELETE(animator);
	SAFE_DELETE(zOrder);
	SAFE_DELETE(enemyinfo);
	SAFE_DELETE(enemyAI);
}

