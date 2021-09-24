#include "stdafx.h"
#include "Lee.h"
#include "LeeIdleState.h"
#include "LeeHitState.h"
#include "LeeDieState.h"

Lee::Lee()
{
	// IDLE
	animator->AddClip("lee_idle_right", CLIPMANAGER->FindClip("lee_idle_right"));
	animator->AddClip("lee_idle_left", CLIPMANAGER->FindClip("lee_idle_left"));
	// WALK
	animator->AddClip("lee_walk_right", CLIPMANAGER->FindClip("lee_walk_right"));
	animator->AddClip("lee_walk_left", CLIPMANAGER->FindClip("lee_walk_left"));
	// RUN
	animator->AddClip("lee_run_right", CLIPMANAGER->FindClip("lee_run_right"));
	animator->AddClip("lee_run_left", CLIPMANAGER->FindClip("lee_run_left"));
	// BLOCK
	animator->AddClip("lee_block_right", CLIPMANAGER->FindClip("lee_block_right"));
	animator->AddClip("lee_block_left", CLIPMANAGER->FindClip("lee_block_left"));
	// HIT
	animator->AddClip("lee_hit_right", CLIPMANAGER->FindClip("lee_hit_right"));
	animator->GetClip("lee_hit_right")->isLoop = false;
	animator->AddClip("lee_hit_left", CLIPMANAGER->FindClip("lee_hit_left"));
	animator->GetClip("lee_hit_left")->isLoop = false;
	// KICK
	animator->AddClip("lee_kick_right", CLIPMANAGER->FindClip("lee_kick_right"));
	animator->GetClip("lee_kick_right")->isLoop = false;
	animator->AddClip("lee_kick_left", CLIPMANAGER->FindClip("lee_kick_left"));
	animator->GetClip("lee_kick_left")->isLoop = false;
	// ATTACK 1
	animator->AddClip("lee_attack1_right", CLIPMANAGER->FindClip("lee_attack1_right"));
	animator->GetClip("lee_attack1_right")->isLoop = false;
	animator->AddClip("lee_attack1_left", CLIPMANAGER->FindClip("lee_attack1_left"));
	animator->GetClip("lee_attack1_left")->isLoop = false;
	// ATTACK 2
	animator->AddClip("lee_attack2_right", CLIPMANAGER->FindClip("lee_attack2_right"));
	animator->GetClip("lee_attack2_right")->isLoop = false;
	animator->AddClip("lee_attack2_left", CLIPMANAGER->FindClip("lee_attack2_left"));
	animator->GetClip("lee_attack2_left")->isLoop = false;
	// ATTACK 3
	animator->AddClip("lee_attack3_right", CLIPMANAGER->FindClip("lee_attack3_right"));
	animator->GetClip("lee_attack3_right")->isLoop = false;
	animator->AddClip("lee_attack3_left", CLIPMANAGER->FindClip("lee_attack3_left"));
	animator->GetClip("lee_attack3_left")->isLoop = false;
	// DIE
	animator->AddClip("lee_die_right", CLIPMANAGER->FindClip("lee_die_right"));
	animator->GetClip("lee_die_right")->isLoop = false;
	animator->AddClip("lee_die_left", CLIPMANAGER->FindClip("lee_die_left"));
	animator->GetClip("lee_die_right")->isLoop = false;


	// AI STATE 동적 할당
	enemyAI->SetState(new LeeIdleState());
}

Lee::~Lee()
{
}

void Lee::Init()
{
	/* 210630 LEE INFO SETTING */
	zOrder->SetZ(transform->GetY() + 132 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	int randomAttackDamage = RND->getInt(5);
	enemyinfo->SetMinDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);

	enemyAI->hitState = new LeeHitState();
	enemyAI->dieState = new LeeDieState();
}
