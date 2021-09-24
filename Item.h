#pragma once
#include "Component.h"

class Item :
    public Component
{
private:
	ZOrder* _zorder;

	float _itemSpeed;						//아이템의 속도
	float _gravity;							//중력
	float _angle;							//각도
	float _friction;						//마찰력

	float _speedX;
	float _speedY;
	float _itemZ;							// player의 z값을 갖고있음

	bool _throwDir;							//던졌을때 방향 설정
	bool _isGround;							//땅에 착지 했는가?

	vector<bool> _isHitThrow;
public:
	Animator* animator;
	GameObject* enemy;

	bool itemAttack;						//아이템으로 공격 했는가?
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
	void ItemAttack();
	void ItemThrowAttack();
   
	void Throw(bool dir);					//던졌을때 방향 설정 함수
	void ChangeClip(string clipName, bool isInitFrame);

	float GetItemZ() const { return _itemZ; }		//player.cpp의 (putItem함수에서 사용)
	void SetItemZ(float itemZ) { _itemZ = itemZ; }	//player의 z값을 얻기 위함
	bool GetItemAttack() const { return itemAttack; }
	Transform* GetEnemyTransform() const { return enemy->transform; }
};