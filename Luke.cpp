#include "stdafx.h"
#include "Luke.h"
#include "LukeIdleState.h"
#include "LukeHitState.h"
#include "LukeDieState.h"

Luke::Luke()
{
	/* 210730 리팩토링 by 대영
	1. 반복문을 활용한 이미지 삽입 */
	string clipNameArr[3];
	clipNameArr[0] = "idle";
	clipNameArr[1] = "walk";
	clipNameArr[2] = "run";
	// 위와 같은 방식으로 "block", "hit" 등 밑에 있는 정보를 추가하면 된다.

	// 반복문을 활용한 이미지 삽입 
	for (int i = 0; i < 3; i++)
	{
		char clipName[32];
		sprintf_s(clipName, "luke_%s_right", clipNameArr[i].c_str());
		animator->AddClip(clipName, CLIPMANAGER->FindClip(clipName));
		sprintf_s(clipName, "luke_%s_left", clipNameArr[i].c_str());
		animator->AddClip(clipName, CLIPMANAGER->FindClip(clipName));
	}


	// IDLE
	animator->AddClip("luke_idle_right", CLIPMANAGER->FindClip("luke_idle_right"));
	animator->AddClip("luke_idle_left", CLIPMANAGER->FindClip("luke_idle_left"));
	// WALK
	animator->AddClip("luke_walk_right", CLIPMANAGER->FindClip("luke_walk_right"));
	animator->AddClip("luke_walk_left", CLIPMANAGER->FindClip("luke_walk_left"));
	// RUN
	animator->AddClip("luke_run_right", CLIPMANAGER->FindClip("luke_run_right"));
	animator->AddClip("luke_run_left", CLIPMANAGER->FindClip("luke_run_left"));
	// BLOCK
	animator->AddClip("luke_block_right", CLIPMANAGER->FindClip("luke_block_right"));
	animator->AddClip("luke_block_left", CLIPMANAGER->FindClip("luke_block_left"));
	// HIT
	animator->AddClip("luke_hit_right", CLIPMANAGER->FindClip("luke_hit_right"));
	animator->GetClip("luke_hit_right")->isLoop = false;
	animator->AddClip("luke_hit_left", CLIPMANAGER->FindClip("luke_hit_left"));
	animator->GetClip("luke_hit_left")->isLoop = false;
	// KICK
	animator->AddClip("luke_kick_right", CLIPMANAGER->FindClip("luke_kick_right"));
	animator->GetClip("luke_kick_right")->isLoop = false;
	animator->AddClip("luke_kick_left", CLIPMANAGER->FindClip("luke_kick_left"));
	animator->GetClip("luke_kick_left")->isLoop = false;
	// ATTACK 1
	animator->AddClip("luke_attack1_right", CLIPMANAGER->FindClip("luke_attack1_right"));
	animator->GetClip("luke_attack1_right")->isLoop = false;
	animator->AddClip("luke_attack1_left", CLIPMANAGER->FindClip("luke_attack1_left"));
	animator->GetClip("luke_attack1_left")->isLoop = false;
	// ATTACK 2
	animator->AddClip("luke_attack2_right", CLIPMANAGER->FindClip("luke_attack2_right"));
	animator->GetClip("luke_attack2_right")->isLoop = false;
	animator->AddClip("luke_attack2_left", CLIPMANAGER->FindClip("luke_attack2_left"));
	animator->GetClip("luke_attack2_left")->isLoop = false;
	// ATTACK 3
	animator->AddClip("luke_attack3_right", CLIPMANAGER->FindClip("luke_attack3_right"));
	animator->GetClip("luke_attack3_right")->isLoop = false;
	animator->AddClip("luke_attack3_left", CLIPMANAGER->FindClip("luke_attack3_left"));
	animator->GetClip("luke_attack3_left")->isLoop = false;
	// DIE
	animator->AddClip("luke_die_right", CLIPMANAGER->FindClip("luke_die_right"));
	animator->GetClip("luke_die_right")->isLoop = false;
	animator->AddClip("luke_die_left", CLIPMANAGER->FindClip("luke_die_left"));
	animator->GetClip("luke_die_left")->isLoop = false;

	// AI STATE 동적 할당
	enemyAI->SetState(new LukeIdleState());
}

Luke::~Luke()
{
}

void Luke::Init()
{
	/* 210629~30 LUKE INFO SETTING */
	zOrder->SetZ(transform->GetY() + 132 / 2);
	
	bool randomDir = RND->getInt(2);
	enemyinfo->SetDir(randomDir);

	enemyinfo->Sethp(50);

	/* 210730 리팩토링 by 대영
	1. 공격할 때 마다 데미지 변경하기 */
	enemyinfo->SetMinDamage(1);
	enemyinfo->SetMaxDamage(5);

	enemyinfo->SetSpeed(48.0f);

	enemyinfo->SetName("luke");

	enemyAI->hitState = new LukeHitState();
	enemyAI->dieState = new LukeDieState();
}