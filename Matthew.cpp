#include "stdafx.h"
#include "Matthew.h"
#include "Matthewstate.h"
#include "Matthewidlestate.h"
#include "Succubus.h"
#include "MatthewPhaseReadyState.h"
#include "MatthewHitState.h"
Matthew::Matthew()
{
}

Matthew::~Matthew()
{
}

void Matthew::Init()
{
	animator = gameObject->GetComponent<Animator>(); // 매튜의 행동 애니메이션
	collision = gameObject->GetComponent<BoxCollider>(); // 매튜의 박스 충돌크기
	zOrder = gameObject->GetComponent<ZOrder>(); // 매튜의 ZOrder 설정
	animator->AddClip("matthew_idle_left", CLIPMANAGER->AddClip("matthew_idle_left", "matthew/idle_left.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_idle_right", CLIPMANAGER->AddClip("matthew_idle_right", "matthew/idle_right.bmp", 686, 136, 6, 0.3f));
	animator->AddClip("matthew_move_left", CLIPMANAGER->AddClip("matthew_move_left", "matthew/move_left.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_move_right", CLIPMANAGER->AddClip("matthew_move_right", "matthew/move_right.bmp", 1160, 136, 10, 0.2f));
	animator->AddClip("matthew_run_left", CLIPMANAGER->AddClip("matthew_run_left", "matthew/run_left.bmp", 1088, 136, 8, 0.2f));
	animator->AddClip("matthew_run_right", CLIPMANAGER->AddClip("matthew_run_right", "matthew/run_right.bmp", 1088, 136, 8, 0.2f));
	animator->AddClip("matthew_attack1_left", CLIPMANAGER->AddClip("matthew_attack1_left", "matthew/attack1_Left.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack1_right", CLIPMANAGER->AddClip("matthew_attack1_right", "matthew/attack1_Right.bmp", 1244, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_left", CLIPMANAGER->AddClip("matthew_attack2_left", "matthew/attack2_Left.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack2_right", CLIPMANAGER->AddClip("matthew_attack2_right", "matthew/attack2_Right.bmp", 1148, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_left", CLIPMANAGER->AddClip("matthew_attack3_left", "matthew/attack3_Left.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_attack3_right", CLIPMANAGER->AddClip("matthew_attack3_right", "matthew/attack3_Right.bmp", 1245, 136, 6, 0.2f));
	animator->AddClip("matthew_palmwind_left", CLIPMANAGER->AddClip("matthew_palmwind_left", "matthew/palm_wind_left.bmp", 6665, 282, 18, 0.1f));
	animator->AddClip("matthew_palmwind_right", CLIPMANAGER->AddClip("matthew_palmwind_right", "matthew/palm_wind_right.bmp", 6665, 282, 18, 0.1f));
	animator->AddClip("matthew_hit_left", CLIPMANAGER->AddClip("matthew_hit_left","matthew/hit_left.bmp",488,117,4,0.3f));
	animator->AddClip("matthew_hit_right", CLIPMANAGER->AddClip("matthew_hit_right","matthew/hit_right.bmp",488,117,4,0.3f));
	animator->AddClip("matthew_block_left",CLIPMANAGER->AddClip("matthew_block_left","matthew/block_left.bmp",468,136,4,0.3f));
	animator->AddClip("matthew_block_right",CLIPMANAGER->AddClip("matthew_block_right","matthew/block_right.bmp",468,136,4,0.3f));
	animator->AddClip("matthew_phase_ready_left", CLIPMANAGER->AddClip("matthew_phase_ready_left","matthew/matthew_phase_ready_left.bmp",648,153,6,0.2f));
	animator->AddClip("matthew_phase_ready_right", CLIPMANAGER->AddClip("matthew_phase_ready_right", "matthew/matthew_phase_ready_right.bmp", 648, 153, 6, 0.2f));
	animator->AddClip("matthew_phase_start_left",CLIPMANAGER->AddClip("matthew_phase_start_left","matthew/phase_start_left.bmp",151,101,1,0.1f));
	animator->AddClip("matthew_phase_start_right", CLIPMANAGER->AddClip("matthew_phase_start_right", "matthew/phase_start_right.bmp", 151, 101, 1, 0.1f));
	animator->AddClip("matthew_phase_spotlight_left", CLIPMANAGER->AddClip("matthew_phase_spotlight_left", "matthew/phase_spotlight_left.bmp", 453, 440, 3, 0.2f));
	animator->AddClip("matthew_phase_spotlight_right", CLIPMANAGER->AddClip("matthew_phase_spotlight_right", "matthew/phase_spotlight_right.bmp", 453, 440, 3, 0.2f));
	animator->AddClip("matthew_phase_end_left", CLIPMANAGER->AddClip("matthew_phase_end_left", "matthew/phase_end_left.bmp", 755, 440, 5, 0.2f));
	animator->AddClip("matthew_phase_end_right", CLIPMANAGER->AddClip("matthew_phase_end_right", "matthew/phase_end_right.bmp", 755, 440, 5, 0.2f));
	animator->AddClip("matthew_lasthit_left",CLIPMANAGER->AddClip("matthew_lasthit_left","matthew/fall_left.bmp",960,136,6,0.3f));
	animator->AddClip("matthew_lasthit_right",CLIPMANAGER->AddClip("matthew_lasthit_right","matthew/fall_Right.bmp",960,136,6,0.3f));
	animator->AddClip("matthew_knockdown_left", CLIPMANAGER->AddClip("matthew_knockdown_left", "matthew/knockdown_left.bmp", 1280, 136, 8, 0.3f));
	animator->AddClip("matthew_knockdown_right", CLIPMANAGER->AddClip("matthew_knockdown_right", "matthew/knockdown_right.bmp", 1280, 136, 8, 0.3f));
	animator->AddClip("matthew_comeback_left", CLIPMANAGER->AddClip("matthew_comeback_left", "matthew/comeback_left.bmp", 1716, 150, 11, 0.2f));
	animator->AddClip("matthew_comeback_right", CLIPMANAGER->AddClip("matthew_comeback_right", "matthew/comeback_right.bmp", 1716, 150, 11, 0.2f));

	CLIPMANAGER->FindClip("matthew_palmwind_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_palmwind_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_ready_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_ready_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_start_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_start_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_end_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_phase_end_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack1_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack1_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack2_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack2_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack3_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_attack3_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_hit_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_hit_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_lasthit_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_lasthit_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_knockdown_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_knockdown_right")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_comeback_left")->isLoop = false;
	CLIPMANAGER->FindClip("matthew_comeback_right")->isLoop = false;

	_hp = 500;
	_speed = 30;
	_gravity = 200;
	hitable = true;
	hitCount = 0;
	_damage = 10;
	_dir = true;
	_attackTime = 0;
	_phaseTime = 0;
	_matthewstate = new MatthewIdleState();
	zOrder->SetZ(transform->GetY() + 136 / 2);
	_matthewstate->Enter(this);

}

void Matthew::Release()
{
}

void Matthew::Update()
{
	Matthewstate* newMatthewstate = _matthewstate->Update(this);
	if (newMatthewstate != nullptr)
	{
		SAFE_DELETE(_matthewstate);
		_matthewstate = newMatthewstate;
		_matthewstate->Enter(this);
	}

	//_phaseTime += TIMEMANAGER->getElapsedTime();
	//if (_phaseTime >= 10)
	//{
	//	_phaseTime = 0;
	//	_matthewstate = new MatthewPhaseReadyState();
	//	_matthewstate->Enter(this);
	//}
}

void Matthew::Render()
{

}

void Matthew::ChangeCilp(string name, bool isInitFrame)
{
	if (isInitFrame == true)
	{
		animator->SetClip(animator->GetClip(name));
	}
	else
	{
		animator->SetClip(animator->GetClip(name), animator->curClip->currentFrame);
	}

}

void Matthew::Hit(int damage)
{
	if (hitable == false) return;
	_hp = damage;
	_matthewstate->Exit(this);
	hitCount++;
	SAFE_DELETE(_matthewstate);
	_matthewstate = new MatthewHitState();
	_matthewstate->Enter(this);
}
