#include "stdafx.h"
#include "Richard.h"
#include "RichardIdleState.h"
#include "RichardHitState.h"
#include "RichardDieState.h"

Richard::Richard()
{
	// IDLE
	animator->AddClip("richard_idle_right", CLIPMANAGER->FindClip("richard_idle_right"));
	animator->AddClip("richard_idle_left", CLIPMANAGER->FindClip("richard_idle_left"));
	// WALK
	animator->AddClip("richard_walk_right", CLIPMANAGER->FindClip("richard_walk_right"));
	animator->AddClip("richard_walk_left", CLIPMANAGER->FindClip("richard_walk_left"));
	// RUN
	animator->AddClip("richard_run_right", CLIPMANAGER->FindClip("richard_run_right"));
	animator->AddClip("richard_run_left", CLIPMANAGER->FindClip("richard_run_left"));
	// BLOCK
	animator->AddClip("richard_block_right", CLIPMANAGER->FindClip("richard_block_right"));
	animator->AddClip("richard_block_left", CLIPMANAGER->FindClip("richard_block_left"));
	// HIT
	animator->AddClip("richard_hit_right", CLIPMANAGER->FindClip("richard_hit_right"));
	animator->GetClip("richard_hit_right")->isLoop = false;
	animator->AddClip("richard_hit_left", CLIPMANAGER->FindClip("richard_hit_left"));
	animator->GetClip("richard_hit_left")->isLoop = false;
	// KICK
	animator->AddClip("richard_kick_right", CLIPMANAGER->FindClip("richard_kick_right"));
	animator->GetClip("richard_kick_right")->isLoop = false;
	animator->AddClip("richard_kick_left", CLIPMANAGER->FindClip("richard_kick_left"));
	animator->GetClip("richard_kick_left")->isLoop = false;
	// ATTACK 1
	animator->AddClip("richard_attack1_right", CLIPMANAGER->FindClip("richard_attack1_right"));
	animator->GetClip("richard_attack1_right")->isLoop = false;
	animator->AddClip("richard_attack1_left", CLIPMANAGER->FindClip("richard_attack1_left"));
	animator->GetClip("richard_attack1_left")->isLoop = false;
	// ATTACK 2
	animator->AddClip("richard_attack2_right", CLIPMANAGER->FindClip("richard_attack2_right"));
	animator->GetClip("richard_attack2_right")->isLoop = false;
	animator->AddClip("richard_attack2_left", CLIPMANAGER->FindClip("richard_attack2_left"));
	animator->GetClip("richard_attack2_left")->isLoop = false;
	// ATTACK 3
	animator->AddClip("richard_attack3_right", CLIPMANAGER->FindClip("richard_attack3_right"));
	animator->GetClip("richard_attack3_right")->isLoop = false;
	animator->AddClip("richard_attack3_left", CLIPMANAGER->FindClip("richard_attack3_left"));
	animator->GetClip("richard_attack3_left")->isLoop = false;
	// DIE
	animator->AddClip("richard_die_right", CLIPMANAGER->FindClip("richard_die_right"));
	animator->GetClip("richard_die_right")->isLoop = false;
	animator->AddClip("richard_die_left", CLIPMANAGER->FindClip("richard_die_left"));
	animator->GetClip("richard_die_left")->isLoop = false;

	// AI STATE 동적 할당
	enemyAI->SetState(new RichardIdleState());
}

Richard::~Richard()
{

}

void Richard::Init()
{
	/* 210630 RICHARD INFO SETTING */
	zOrder->SetZ(transform->GetY() + 132 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	int randomAttackDamage = RND->getInt(5);
	enemyinfo->SetMinDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);

	enemyAI->hitState = new RichardHitState();
	enemyAI->dieState = new RichardDieState();
}
