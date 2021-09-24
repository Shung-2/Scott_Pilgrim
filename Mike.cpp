#include "stdafx.h"
#include "Mike.h"
#include "MikeIdleState.h"
#include "MikeHitState.h"
#include "MikeDieState.h"

Mike::Mike()
{
	// IDLE
	animator->AddClip("mike_idle_right", CLIPMANAGER->FindClip("mike_idle_right"));
	animator->AddClip("mike_idle_left", CLIPMANAGER->FindClip("mike_idle_left"));
	// WALK
	animator->AddClip("mike_walk_right", CLIPMANAGER->FindClip("mike_walk_right"));
	animator->AddClip("mike_walk_left", CLIPMANAGER->FindClip("mike_walk_left"));
	// RUN
	animator->AddClip("mike_run_right", CLIPMANAGER->FindClip("mike_run_right"));
	animator->AddClip("mike_run_left", CLIPMANAGER->FindClip("mike_run_left"));
	// BLOCK
	animator->AddClip("mike_block_right", CLIPMANAGER->FindClip("mike_block_right"));
	animator->AddClip("mike_block_left", CLIPMANAGER->FindClip("mike_block_left"));
	// HIT
	animator->AddClip("mike_hit_right", CLIPMANAGER->FindClip("mike_hit_right"));
	animator->GetClip("mike_hit_right")->isLoop = false;
	animator->AddClip("mike_hit_left", CLIPMANAGER->FindClip("mike_hit_left"));
	animator->GetClip("mike_hit_left")->isLoop = false;
	// KICK
	animator->AddClip("mike_kick_right", CLIPMANAGER->FindClip("mike_kick_right"));
	animator->GetClip("mike_kick_right")->isLoop = false;
	animator->AddClip("mike_kick_left", CLIPMANAGER->FindClip("mike_kick_left"));
	animator->GetClip("mike_kick_left")->isLoop = false;
	// ATTACK 1
	animator->AddClip("mike_attack1_right", CLIPMANAGER->FindClip("mike_attack1_right"));
	animator->GetClip("mike_attack1_right")->isLoop = false;
	animator->AddClip("mike_attack1_left", CLIPMANAGER->FindClip("mike_attack1_left"));
	animator->GetClip("mike_attack1_left")->isLoop = false;
	// ATTACK 2
	animator->AddClip("mike_attack2_right", CLIPMANAGER->FindClip("mike_attack2_right"));
	animator->GetClip("mike_attack2_right")->isLoop = false;
	animator->AddClip("mike_attack2_left", CLIPMANAGER->FindClip("mike_attack2_left"));
	animator->GetClip("mike_attack2_left")->isLoop = false;
	// ATTACK 3
	animator->AddClip("mike_attack3_right", CLIPMANAGER->FindClip("mike_attack3_right"));
	animator->GetClip("mike_attack3_right")->isLoop = false;
	animator->AddClip("mike_attack3_left", CLIPMANAGER->FindClip("mike_attack3_left"));
	animator->GetClip("mike_attack3_left")->isLoop = false;
	// DIE
	animator->AddClip("mike_die_right", CLIPMANAGER->FindClip("mike_die_right"));
	animator->GetClip("mike_die_right")->isLoop = false;
	animator->AddClip("mike_die_left", CLIPMANAGER->FindClip("mike_die_left"));
	animator->GetClip("mike_die_left")->isLoop = false;

	// AI STATE 동적 할당
	enemyAI->SetState(new MikeIdleState());
}

Mike::~Mike()
{
}

void Mike::Init()
{
	/* 210701 MIKE INFO SETTING */
	zOrder->SetZ(transform->GetY() + 132 / 2);

	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	int randomAttackDamage = RND->getInt(5);
	enemyinfo->SetMinDamage(randomAttackDamage);

	enemyinfo->SetSpeed(48.0f);

	enemyAI->hitState = new MikeHitState();
	enemyAI->dieState = new MikeDieState();
}
