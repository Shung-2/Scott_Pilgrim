#pragma once
#include "Component.h"
class PlayerState;
//class Enemy;

class Player :
	public Component
{
private:
	float _speed;		//플레이어 속도
	float _gravity;		//중력
	
	int _enterNum;		//플레이어와 gameObject가 겹칠때++
	int _exitNum;		//플레이어와 gameObject가 겹쳐짐이 끝낫을떄++
	
	//float _friction;	//마찰

	PlayerState* _state;

	AnimationClip idleRight;
	AnimationClip idleLeft;
	AnimationClip walkRight;
	AnimationClip walkLeft;
	AnimationClip runRight;
	AnimationClip runLeft;
	AnimationClip jumpRight;
	AnimationClip jumpLeft;
	AnimationClip fallRight;
	AnimationClip fallLeft;
	AnimationClip jumpZorderRight;
	AnimationClip jumpZorderLeft;
	AnimationClip groundRight;
	AnimationClip groundLeft;
	AnimationClip attack1Right;
	AnimationClip attack2Right;
	AnimationClip attack3Right;
	AnimationClip attack4Right;
	AnimationClip attack1Left;
	AnimationClip attack2Left;
	AnimationClip attack3Left;
	AnimationClip attack4Left;
	AnimationClip kickAttackRight;
	AnimationClip kickAttackLeft;
	AnimationClip kickSkillRight;
	AnimationClip kickSkillLeft;
	AnimationClip walkJumpKickRight;
	AnimationClip walkJumpKickLeft;
	AnimationClip runJumpKickRight;
	AnimationClip runJumpKickLeft;
	AnimationClip shieldRight;
	AnimationClip shieldLeft;
	AnimationClip hit1Right;
	AnimationClip hit2Right;
	AnimationClip hit1Left;
	AnimationClip hit2Left;
	AnimationClip lastHitRight;
	AnimationClip lastHitLeft;
	AnimationClip knockoutRight;
	AnimationClip knockoutLeft;
	AnimationClip hitJumpRight;
	AnimationClip hitJumpLeft;
	AnimationClip wakeupRight;
	AnimationClip wakeupLeft;

	//두손이미지
	AnimationClip twoHandPickRight;
	AnimationClip twoHandPickLeft;
	AnimationClip twoHandIdleRight;
	AnimationClip twoHandIdleLeft;
	AnimationClip twoHandWalkRight;
	AnimationClip twoHandWalkLeft;
	AnimationClip twoHandRunRight;
	AnimationClip twoHandRunLeft;
	AnimationClip twoHandJumpRight;
	AnimationClip twoHandJumpLeft;
	AnimationClip twoHandFallRight;
	AnimationClip twoHandFallLeft;
	AnimationClip twoHandGroundRight;
	AnimationClip twoHandGroundLeft;
	AnimationClip twoHandZorderRight;
	AnimationClip twoHandZorderLeft;
	AnimationClip twoHandWalkAttackRight;
	AnimationClip twoHandWalkAttackLeft;
	AnimationClip twoHandWalkThrowRight;
	AnimationClip twoHandWalkThrowLeft;
	AnimationClip twoHandRunAttackRight;
	AnimationClip twoHandRunAttackLeft;



public:
	BoxCollider* collider;
	Ground* ground;
	Animator* animator;
	ZOrder* zOrder;
	Item* item;
	GameObject* equipItem;
	GameObject* enemy;

	GameObject* boss;
	bool dir;				//오른쪽 왼쪽 구분
	bool jumpZ;				//Z축 점프 구분
	bool isZJump;			//Z축 그라운드 체크 구분
	bool isRun;				//뛰는 거 구분
	bool runKeyPress;		//키 더블했는지
	bool block;				//막기 구분
	bool dirZ;				//Z축 (true -> 위/ false->아래)
	bool onGround;			//그라운드 인지 여부
	bool isCatch;			//아이템을 획득 유무 
	bool isPick;			//아이템을 들어올렸는지 유무
	bool isThrow;			//아이템을 던졌는가?
	bool isUppercut;		//어퍼컷 유무
	bool pressL;			//L키 누른 거 여부
	bool hitable;			//공격 가능 여부
	bool isJump;			//점프 여부

	float runDelay;			//뛸 때 딜레이 시간 줄 때
	float jumpDelay;		//z축 위아래 점프 딜레이 시간 줄때
	float pickDelay;		//줍는 시간 딜레이
	float throwDelay;		//던지는 시간 딜레이
	float friction;			//마찰
	float jumpPower;		//점프력

	int hp;					//플레이어 hp
	int damage;				//플레이어 공격력 (추후 레벨 별 구분)
	int skillDamage;		//플레이어 스킬 공격력
	int hitCount;			//타격 맞은 횟수


	RECT groundCheckRc;

	void InputHandle();
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void ChangeClip(string clipName, bool isInitFrame);
	void ClipInit();

	int GetSpeed() const { return _speed; }
	int GetGravity() const { return _gravity; }
	int GetFriction() const { return friction; }
	//int GetFriction1() const { return }
	virtual void OnTriggerEnter(GameObject* gameObject);
	virtual void OnTriggerExit(GameObject* gameObject);

	virtual void PickItem();		//아이템 획득 함수
	virtual void PutItem();			//아이템 놓는 함수

	Transform* GetItemTransform() const { return equipItem->transform; }
	Item* GetItem() const { return item; }
	void SetEnemy(GameObject* _enemy) { enemy = _enemy; }
	Transform* GetEnemyTransform() const { return enemy -> transform; }

	/* Player.h */
	/* 210630 Enemy 충돌(Hit)를 위한 함수 생성 by. 시영 */
	void Hit(int damage);
	void BossAttack();
};

