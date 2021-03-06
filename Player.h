#pragma once
#include "Component.h"
class PlayerState;
//class Enemy;

class Player :
	public Component
{
private:
	float _speed;		//?÷??̾? ?ӵ?
	float _gravity;		//?߷?
	
	int _enterNum;		//?÷??̾??? gameObject?? ??ĥ??++
	int _exitNum;		//?÷??̾??? gameObject?? ???????? ????????++
	
	//float _friction;	//????

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

	//?μ??̹???
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
	bool dir;				//?????? ???? ????
	bool jumpZ;				//Z?? ???? ????
	bool isZJump;			//Z?? ?׶????? üũ ????
	bool isRun;				//?ٴ? ?? ????
	bool runKeyPress;		//Ű ?????ߴ???
	bool block;				//???? ????
	bool dirZ;				//Z?? (true -> ??/ false->?Ʒ?)
	bool onGround;			//?׶????? ???? ????
	bool isCatch;			//???????? ȹ?? ???? 
	bool isPick;			//???????? ?????÷ȴ??? ????
	bool isThrow;			//???????? ?????°??
	bool isUppercut;		//?????? ????
	bool pressL;			//LŰ ???? ?? ????
	bool hitable;			//???? ???? ????
	bool isJump;			//???? ????

	float runDelay;			//?? ?? ?????? ?ð? ?? ??
	float jumpDelay;		//z?? ???Ʒ? ???? ?????? ?ð? ?ٶ?
	float pickDelay;		//?ݴ? ?ð? ??????
	float throwDelay;		//?????? ?ð? ??????
	float friction;			//????
	float jumpPower;		//??????

	int hp;					//?÷??̾? hp
	int damage;				//?÷??̾? ???ݷ? (???? ???? ?? ????)
	int skillDamage;		//?÷??̾? ??ų ???ݷ?
	int hitCount;			//Ÿ?? ???? Ƚ??


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

	virtual void PickItem();		//?????? ȹ?? ?Լ?
	virtual void PutItem();			//?????? ???? ?Լ?

	Transform* GetItemTransform() const { return equipItem->transform; }
	Item* GetItem() const { return item; }
	void SetEnemy(GameObject* _enemy) { enemy = _enemy; }
	Transform* GetEnemyTransform() const { return enemy -> transform; }

	/* Player.h */
	/* 210630 Enemy ?浹(Hit)?? ???? ?Լ? ???? by. ?ÿ? */
	void Hit(int damage);
	void BossAttack();
};

