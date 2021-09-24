#include "stdafx.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerHitState.h"

void Player::InputHandle()
{
	PlayerState* newState = _state->InputHandle(this);
	if (newState != nullptr)
	{
		_state->Exit(this);
		SAFE_DELETE(_state);
		_state = newState;
		_state->Enter(this);
	}
}

void Player::Init()
{
	animator = gameObject->GetComponent<Animator>();
	collider = gameObject->GetComponent<BoxCollider>();
	ground = gameObject->GetComponent<Ground>();
	zOrder = gameObject->GetComponent<ZOrder>();

	ClipInit();
	_speed = 100;							//플레이어 속도
	_gravity = 200;							//플레이어 중력 (점프 후 중력값)
	friction = 130;							//플레이어 마찰 (런뛰고 미끄러질 때)
	jumpPower = 200;						//플레이어 점프력

	dir = false;							//좌우 확인 용
	dirZ = false;							//Z축 확인용
	isRun = false;							//플레이어가 뛰는 지 유무
	runKeyPress = false;					//뛰는 키를 눌렀는 지 유무
	jumpZ = false;							//Z축 점프 확인용
	block = false;							//막기 확인용
	isZJump = false;						//Z축 점프 시 플레이어 그라운드 착지 확인용
	onGround = false;
	isPick = false;							//아이템을 주었는지 유무
	isCatch = false;						//아이템을 잡았는지 유무
	isUppercut = false;
	pressL = false;
	hitable = true;
	isJump = false;

	_state = new PlayerIdleState();			//Idle 상태로 초기화
	_state->Enter(this);
	runDelay = 0;
	jumpDelay = 0;
	pickDelay = 0;
	throwDelay = 0;

	hp = 100;
	damage = 50;
	skillDamage = 6;
	isUppercut = false;
	pressL = false;
	hitCount = 0;
}

void Player::Update()
{
	InputHandle();
	groundCheckRc = RectMakeCenter(transform->GetX(), transform->GetY() + collider->height / 2 + 5,
		collider->width, 10);
	_state->Update(this);
	if (runKeyPress == true)
		runDelay += TIMEMANAGER->getElapsedTime();
	if (jumpZ == true)
		jumpDelay += TIMEMANAGER->getElapsedTime();

	if (isCatch == true)
	{
		equipItem->GetComponent<ZOrder>()->SetZ(zOrder->GetZ() - 1);
		//equipItem = item->gameObject;
		//equipItem->GetComponent<Item>()->transform->GetChild(1);
	}
	if (isPick == true)
	{
		pickDelay += TIMEMANAGER->getElapsedTime();
		if (pickDelay >= 0.3f)
		{
			if (!dir)
			{
				item->transform->SetPosition(transform->GetX() - 14, transform->GetY() - 77);
			}
			if (dir)
			{
				item->transform->SetPosition(transform->GetX() + 14, transform->GetY() - 77);
			}
			pickDelay = 0;
			isPick = false;
		}
	}
	if (isThrow == true)
	{
		equipItem = item->gameObject;
		equipItem->GetComponent<Item>()->itemAttack = true;
		throwDelay += TIMEMANAGER->getElapsedTime();
		if (throwDelay >= 0.4f)
		{
			PutItem();
			isThrow = false;	
			throwDelay = 0;
		}
	}
}

void Player::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		HPEN hPen, oPen;
		HBRUSH hBrush, oBrush;

		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oBrush = (HBRUSH)SelectObject(BackBuffer, hBrush);
		hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));
		oPen = (HPEN)SelectObject(BackBuffer, hPen);
		Rectangle(BackBuffer, groundCheckRc);
		SelectObject(BackBuffer, oPen);
		SelectObject(BackBuffer, oBrush);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
}

void Player::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
	}
	else
	{
		animator->SetClip(animator->GetClip(clipName));
	}
}

void Player::ClipInit()
{
	idleRight.Init("player/idle_right.bmp", 640, 122, 8, 0.20f);
	idleLeft.Init("player/idle_left.bmp", 640, 122, 8, 0.20f);
	walkRight.Init("player/walk_right.bmp", 456, 128, 6, 0.25f);
	walkLeft.Init("player/walk_left.bmp", 456, 128, 6, 0.25f);
	runRight.Init("player/run_right.bmp", 864, 126, 8, 0.17f);
	runLeft.Init("player/run_left.bmp", 864, 126, 8, 0.17f);
	jumpRight.Init("player/jump_right.bmp", 686, 144, 7, 0.15f);
	jumpRight.isLoop = false;
	jumpLeft.Init("player/jump_left.bmp", 686, 144, 7, 0.15f);
	jumpLeft.isLoop = false;
	fallRight.Init("player/fall_right.bmp", 490, 144, 5, 0.15f);
	fallRight.isLoop = false;
	fallLeft.Init("player/fall_left.bmp", 490, 144, 5, 0.15f);
	fallLeft.isLoop = false;
	jumpZorderRight.Init("player/jump_Zorder_right.bmp", 882, 144, 9, 0.08f);
	jumpZorderRight.isLoop = false;
	jumpZorderLeft.Init("player/jump_Zorder_left.bmp", 882, 144, 9, 0.08f);
	jumpZorderLeft.isLoop = false;
	groundRight.Init("player/ground_right.bmp", 98, 144, 1, 0.10f);
	groundRight.isLoop = false;
	groundLeft.Init("player/ground_left.bmp", 98, 144, 1, 0.10f);
	groundLeft.isLoop = false;

	shieldRight.Init("player/block_right.bmp", 532, 126, 7, 0.22f);
	shieldRight.isLoop = false;
	shieldLeft.Init("player/block_left.bmp", 532, 126, 7, 0.22f);
	shieldLeft.isLoop = false;

	wakeupRight.Init("player/wakeup_right.bmp", 966, 134, 7, 0.22f);
	wakeupRight.isLoop = false;
	wakeupLeft.Init("player/wakeup_left.bmp", 966, 134, 7, 0.22f);
	wakeupLeft.isLoop = false;




	//공격 이미지
	attack1Right.Init("player/attack1_right.bmp", 456, 120, 3, 0.1f);
	attack2Right.Init("player/attack2_right.bmp", 608, 120, 4, 0.1f);
	attack3Right.Init("player/attack3_right.bmp", 456, 120, 3, 0.15f);
	attack4Right.Init("player/attack4_right.bmp", 864, 196, 8, 0.15f);

	attack1Right.isLoop = false;
	attack2Right.isLoop = false;
	attack3Right.isLoop = false;
	attack4Right.isLoop = false;

	attack1Left.Init("player/attack1_left.bmp", 456, 120, 3, 0.1f);
	attack2Left.Init("player/attack2_left.bmp", 608, 120, 4, 0.1f);
	attack3Left.Init("player/attack3_left.bmp", 456, 120, 3, 0.15f);
	attack4Left.Init("player/attack4_left.bmp", 864, 196, 8, 0.15f);

	attack1Left.isLoop = false;
	attack2Left.isLoop = false;
	attack3Left.isLoop = false;
	attack4Left.isLoop = false;

	//맞는 이미지
	hit1Right.Init("player/hit1_right.bmp", 258, 138, 3, 0.12f);
	hit2Right.Init("player/hit2_right.bmp", 400, 122, 4, 0.12f);
	lastHitRight.Init("player/last_hit_right.bmp", 816, 184, 6, 0.15f);
	knockoutRight.Init("player/knockout_right.bmp", 426, 78, 3, 0.15f);
	hit1Right.isLoop = false;
	hit2Right.isLoop = false;
	lastHitRight.isLoop = false;
	knockoutRight.isLoop = false;

	hit1Left.Init("player/hit1_left.bmp", 258, 138, 3, 0.12f);
	hit2Left.Init("player/hit2_left.bmp", 400, 122, 4, 0.12f);
	lastHitLeft.Init("player/last_hit_left.bmp", 816, 184, 6, 0.15f);
	knockoutLeft.Init("player/knockout_left.bmp", 426, 78, 3, 0.15f);

	hit1Left.isLoop = false;
	hit2Left.isLoop = false;
	lastHitLeft.isLoop = false;
	knockoutLeft.isLoop = false;

	kickAttackRight.Init("player/kick_attack_right.bmp", 896, 126, 7, 0.15f);
	kickAttackRight.isLoop = false;
	kickAttackLeft.Init("player/kick_attack_left.bmp", 896, 126, 7, 0.15f);
	kickAttackLeft.isLoop = false;
	kickSkillRight.Init("player/kick_skill_right.bmp", 7958, 152, 23, 0.1f);
	kickSkillRight.isLoop = false;
	kickSkillLeft.Init("player/kick_skill_left.bmp", 7958, 152, 23, 0.1f);
	kickSkillLeft.isLoop = false;

	walkJumpKickRight.Init("player/walk_jump_kick_right.bmp", 980, 106, 7, 0.1f);
	walkJumpKickRight.isLoop = false;
	walkJumpKickLeft.Init("player/walk_jump_kick_left.bmp", 980, 106, 7, 0.1f);
	walkJumpKickLeft.isLoop = false;
	runJumpKickRight.Init("player/run_jump_kick_right.bmp", 1036, 102, 7, 0.15f);
	runJumpKickRight.isLoop = false;
	runJumpKickLeft.Init("player/run_jump_kick_left.bmp", 1036, 102, 7, 0.15f);
	runJumpKickLeft.isLoop = false;

	//두손 이미지
	twoHandPickRight.Init("player/two_hand_pick_right.bmp", 192, 130, 2, 0.20f);
	twoHandPickRight.isLoop = false;
	twoHandPickLeft.Init("player/two_hand_pick_left.bmp", 192, 130, 2, 0.20f);
	twoHandPickLeft.isLoop = false;
	twoHandIdleRight.Init("player/two_hand_idle_right.bmp", 312, 120, 4, 0.20f);
	twoHandIdleLeft.Init("player/two_hand_idle_left.bmp", 312, 120, 4, 0.20f);
	twoHandWalkRight.Init("player/two_hand_walk_right.bmp", 468, 130, 6, 0.25f);
	twoHandWalkLeft.Init("player/two_hand_walk_left.bmp", 468, 130, 6, 0.25f);
	twoHandRunRight.Init("player/two_hand_run_right.bmp", 944, 120, 8, 0.17f);
	twoHandRunLeft.Init("player/two_hand_run_left.bmp", 944, 120, 8, 0.17f);
	twoHandJumpRight.Init("player/two_hand_jump_right.bmp", 658, 146, 7, 0.15f);
	twoHandJumpRight.isLoop = false;
	twoHandJumpLeft.Init("player/two_hand_jump_left.bmp", 658, 146, 7, 0.15f);
	twoHandJumpLeft.isLoop = false;
	twoHandFallRight.Init("player/two_hand_fall_right.bmp", 470, 146, 5, 0.15f);
	twoHandFallRight.isLoop = false;
	twoHandFallLeft.Init("player/two_hand_fall_left.bmp", 470, 146, 5, 0.15f);
	twoHandFallLeft.isLoop = false;
	twoHandGroundRight.Init("player/two_hand_ground_right.bmp", 94, 146, 1, 0.10f);
	twoHandGroundRight.isLoop = false;
	twoHandGroundLeft.Init("player/two_hand_ground_left.bmp", 94, 146, 1, 0.10f);
	twoHandGroundLeft.isLoop = false;
	twoHandZorderRight.Init("player/two_hand_Zorder_right.bmp", 768, 146, 8, 0.08f);
	twoHandZorderRight.isLoop = false;
	twoHandZorderLeft.Init("player/two_hand_Zorder_left.bmp", 768, 146, 8, 0.08f);
	twoHandZorderLeft.isLoop = false;

	twoHandWalkAttackRight.Init("player/two_hand_walk_attack_right.bmp", 938, 126, 7, 0.2f);
	twoHandWalkAttackRight.isLoop = false;
	twoHandWalkAttackLeft.Init("player/two_hand_walk_attack_left.bmp", 938, 126, 7, 0.2f);
	twoHandWalkAttackLeft.isLoop = false;

	twoHandWalkThrowRight.Init("player/two_hand_walk_throw_right.bmp", 756, 136, 7, 0.2f);
	twoHandWalkThrowRight.isLoop = false;
	twoHandWalkThrowLeft.Init("player/two_hand_walk_throw_left.bmp", 756, 136, 7, 0.2f);
	twoHandWalkThrowLeft.isLoop = false;


	twoHandRunAttackRight.Init("player/two_hand_run_attack_right.bmp", 756, 138, 6, 0.15f);
	twoHandRunAttackRight.isLoop = false;
	twoHandRunAttackLeft.Init("player/two_hand_run_attack_left.bmp", 756, 138, 6, 0.15f);
	twoHandRunAttackLeft.isLoop = false;



	animator->AddClip("idle_right", &idleRight);
	animator->AddClip("idle_left", &idleLeft);
	animator->AddClip("walk_right", &walkRight);
	animator->AddClip("walk_left", &walkLeft);
	animator->AddClip("run_right", &runRight);
	animator->AddClip("run_left", &runLeft);
	animator->AddClip("jump_right", &jumpRight);
	animator->AddClip("jump_left", &jumpLeft);
	animator->AddClip("fall_right", &fallRight);
	animator->AddClip("fall_left", &fallLeft);
	animator->AddClip("jump_Zorder_right", &jumpZorderRight);
	animator->AddClip("jump_Zorder_left", &jumpZorderLeft);
	animator->AddClip("ground_right", &groundRight);
	animator->AddClip("ground_left", &groundLeft);
	animator->AddClip("wakeup_right", &wakeupRight);
	animator->AddClip("wakeup_left", &wakeupLeft);

	animator->AddClip("block_right", &shieldRight);
	animator->AddClip("block_left", &shieldLeft);

	animator->AddClip("kick_attack_right", &kickAttackRight);
	animator->AddClip("kick_attack_left", &kickAttackLeft);
	animator->AddClip("kick_skill_right", &kickSkillRight);
	animator->AddClip("kick_skill_left", &kickSkillLeft);
	animator->AddClip("walk_jump_kick_right", &walkJumpKickRight);
	animator->AddClip("walk_jump_kick_left", &walkJumpKickLeft);
	animator->AddClip("run_jump_kick_right", &runJumpKickRight);
	animator->AddClip("run_jump_kick_left", &runJumpKickLeft);

	animator->AddClip("attack1_right", &attack1Right);
	animator->AddClip("attack2_right", &attack2Right);
	animator->AddClip("attack3_right", &attack3Right);
	animator->AddClip("attack4_right", &attack4Right);
	animator->AddClip("attack1_left", &attack1Left);
	animator->AddClip("attack2_left", &attack2Left);
	animator->AddClip("attack3_left", &attack3Left);
	animator->AddClip("attack4_left", &attack4Left);


	animator->AddClip("hit1_right", &hit1Right);
	animator->AddClip("hit2_right", &hit2Right);
	animator->AddClip("last_hit_right", &lastHitRight);
	animator->AddClip("knockout_right", &knockoutRight);
	animator->AddClip("hit1_left",  &hit1Left);
	animator->AddClip("hit2_left",  &hit2Left);
	animator->AddClip("last_hit_left",  &lastHitLeft);
	animator->AddClip("knockout_left", &knockoutLeft);

	//두손 이미지

	animator->AddClip("two_hand_idle_right", &twoHandIdleRight);
	animator->AddClip("two_hand_idle_left", &twoHandIdleLeft);
	animator->AddClip("two_hand_pick_right", &twoHandPickRight);
	animator->AddClip("two_hand_pick_left", &twoHandPickLeft);
	animator->AddClip("two_hand_walk_right", &twoHandWalkRight);
	animator->AddClip("two_hand_walk_left", &twoHandWalkLeft);
	animator->AddClip("two_hand_run_right", &twoHandRunRight);
	animator->AddClip("two_hand_run_left", &twoHandRunLeft);
	animator->AddClip("two_hand_jump_right", &twoHandJumpRight);
	animator->AddClip("two_hand_jump_left", &twoHandJumpLeft);
	animator->AddClip("two_hand_fall_right", &twoHandFallRight);
	animator->AddClip("two_hand_fall_left", &twoHandFallLeft);
	animator->AddClip("two_hand_ground_right", &twoHandGroundRight);
	animator->AddClip("two_hand_ground_left", &twoHandGroundLeft);
	animator->AddClip("two_hand_Zorder_right", &twoHandZorderRight);
	animator->AddClip("two_hand_Zorder_left", &twoHandZorderLeft);
	animator->AddClip("two_hand_walk_attack_right", &twoHandWalkAttackRight);
	animator->AddClip("two_hand_walk_attack_left", &twoHandWalkAttackLeft);
	animator->AddClip("two_hand_run_attack_right", &twoHandRunAttackRight);
	animator->AddClip("two_hand_run_attack_left", &twoHandRunAttackLeft);
	animator->AddClip("two_hand_walk_throw_right", &twoHandWalkThrowRight);
	animator->AddClip("two_hand_walk_throw_left", &twoHandWalkThrowLeft);

	animator->AddTransaction("pickup_to_pickup_idle_right", &twoHandPickRight, &twoHandIdleRight);
	animator->AddTransaction("pickup_to_pickup_idle_left", &twoHandPickLeft, &twoHandIdleLeft);
	animator->AddTransaction("throw_idle_right", &twoHandWalkThrowRight, &idleRight);
	animator->AddTransaction("throw_idle_left", &twoHandWalkThrowLeft, &idleLeft);
	
}

void Player::OnTriggerEnter(GameObject * gameObject)
{
	item = gameObject->GetComponent<Item>();
}

void Player::OnTriggerExit(GameObject * gameObject)
{
	item = nullptr;
}

void Player::PickItem()								// item 획득 했을때
{
	if (transform->GetChildCount() == 0)			//player가 자식이 없을때
	{
		transform->AddChild(item->transform);		//player는 item을 자식으로 가지고
		//transform->GetChild(1)->DetachParent();
		isCatch = true;								//item을 가지고 있는 상태가 된다
		equipItem = item->gameObject;
		equipItem->GetComponent<ZOrder>()->SetZ(zOrder->GetZ());
	}
}


void Player::PutItem()															//item을 놓았을때
{
	if (equipItem != nullptr)													//item이 값을 가지고 있을때
	{
		equipItem->transform->DetachParent();									//item은 부모를 잃는다
		equipItem->GetComponent<Item>()->SetItemZ(this->zOrder->GetZ());		//던졌을때 itemz는 player의 z값을 가진다
		equipItem->GetComponent<Item>()->Throw(dir);							//dir에 따른 throw	
		equipItem = nullptr;													
	}	
	isCatch = false;															//item이 없는 상태이고
	item = nullptr;																//item은 값을 잃는다	
}

void Player::Hit(int damage)
{
	if (block == true && isCatch == false)
	{
		if (dir == false)
		{
			EFFECTMANAGER->EmissionEffect("block_effect", transform->GetX() + 30, transform->GetY() - 10);
		}
		else
		{
			EFFECTMANAGER->EmissionEffect("block_effect", transform->GetX() - 30, transform->GetY() - 10);
		}
		return;
	} 

	//if (hitable == false) return;
	DAMAGEMANAGER->CreateDamage(damage, transform->GetX(), transform->GetY() - 70);
	hp -= damage;
	_state->Exit(this);
	if (hitable == false) return;
	hitCount++;

	if (isCatch == true && hitCount >= 1)
	{
		
		//transform->GetChild(1)->DetachParent();
		//equipItem = item->gameObject;
		//equipItem->GetComponent<Item>()->transform->GetChild(1);
		//transform->DetachChild(1);
		//equipItem = item->gameObject;
		//equipItem->GetComponent<Item>()->transform->DetachParent();
		//transform->DetachChild(1);
		//equipItem->GetComponent<Item>()->transform->DetachParent();
		//item = nullptr;
		//transform->DetachChild(1);
		//transform->GetChild(1)->DetachChild(1);
	}

	//_state = new PlayerHitState();
	//_state->Enter(this);
	if (hp <= 0)
	{
		//gameObject->SetActive(false);
		// TODO - DEAD
	}
}

void Player::BossAttack()
{
	float distance =
		GetDistance(transform->GetX(), transform->GetY(),
			boss->transform->GetX(), boss->transform->GetY());
	float distanceZ = zOrder->GetZ() - boss->GetComponent<ZOrder>()->GetZ();
	if (distanceZ < 0)
		distanceZ *= -1;
	if (distance < 100 && distanceZ < 10)
	{
		boss->GetComponent<Matthew>()->Hit(damage);
		if (boss->GetComponent<Matthew>()->hitable == true)
		{
			if (dir == false)
				EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX() + 30, transform->GetY() - 10);
			else
				EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX() - 30, transform->GetY() - 10);
		}
	}
}


