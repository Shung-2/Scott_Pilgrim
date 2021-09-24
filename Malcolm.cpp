#include "stdafx.h"
#include "EnemyState.h"
#include "Malcolm.h"
#include "MalcolmIdleState.h"
#include "MalcolmhitState.h"
#include "MalcolmDieState.h"
Malcolm::Malcolm()
{
	CLIPMANAGER->FindClip("malcolm_attack_left")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_attack_right")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_kick_left")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_kick_right")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_block_left")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_block_right")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_hit_left")->isLoop = false;
	CLIPMANAGER->FindClip("malcolm_hit_right")->isLoop = false;

	animator->AddClip("malcolm_idle_left", CLIPMANAGER->FindClip("malcolm_idle_left"));
	animator->AddClip("malcolm_idle_right", CLIPMANAGER->FindClip("malcolm_idle_right"));
	animator->AddClip("malcolm_move_left", CLIPMANAGER->FindClip("malcolm_move_left"));
	animator->AddClip("malcolm_move_right", CLIPMANAGER->FindClip("malcolm_move_right"));
	animator->AddClip("malcolm_run_left", CLIPMANAGER->FindClip("malcolm_run_left"));
	animator->AddClip("malcolm_run_right", CLIPMANAGER->FindClip("malcolm_run_right"));
	animator->AddClip("malcolm_attack_left", CLIPMANAGER->FindClip("malcolm_attack_left"));
	animator->AddClip("malcolm_attack_right", CLIPMANAGER->FindClip("malcolm_attack_right"));
	animator->AddClip("malcolm_kick_left",CLIPMANAGER->FindClip("malcolm_kick_left"));
	animator->AddClip("malcolm_kick_right",CLIPMANAGER->FindClip("malcolm_kick_right"));
	animator->AddClip("malcolm_block_left",CLIPMANAGER->FindClip("malcolm_block_left"));
	animator->AddClip("malcolm_block_right",CLIPMANAGER->FindClip("malcolm_block_right"));
	animator->AddClip("malcolm_hit_left", CLIPMANAGER->FindClip("malcolm_hit_left"));
	animator->AddClip("malcolm_hit_right", CLIPMANAGER->FindClip("malcolm_hit_right"));
	

	enemyAI->SetState(new MalcolmIdleState);
}

Malcolm::~Malcolm()
{
}

void Malcolm::Init()
{
	zOrder->SetZ(transform->GetY() + 158 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	//int randomAttackDamage = RND->getInt(10);
	int randomAttackDamage = 0;

	//int randomAttackDamage = RND->getInt(5);
	enemyinfo->SetMinDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);

	enemyAI->hitState = new MalcolmHitState();
	enemyAI->dieState = new MalcolmDieState();
}
