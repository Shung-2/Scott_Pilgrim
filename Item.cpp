#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	animator->AddClip("trashbox_left", CLIPMANAGER->FindClip("trashbox_left"));
	animator->AddClip("trashbox_walk_attack_right", CLIPMANAGER->FindClip("trashbox_walk_attack_right"));
	animator->AddClip("trashbox_walk_attack_left", CLIPMANAGER->FindClip("trashbox_walk_attack_left"));

	animator->AddClip("trashbox_walk_throw_right", CLIPMANAGER->FindClip("trashbox_walk_throw_right"));
	animator->AddClip("trashbox_walk_throw_left", CLIPMANAGER->FindClip("trashbox_walk_throw_left"));

	_itemSpeed = 320.f;		// 아이템의 속도
	_gravity = 560.f;
	_friction = 60.f;		// 마찰력
							//위 값들은 변하지 않기에 init에서 값 줌

	_angle = 0.f;			// 각도
	_itemZ = 0.f;			// 플레이어의 Z 값을 가져오기 위한 변수
	
	_speedX = 0.f;			// 스피드와 앵글 값을 이용하기 위한 변수
	_speedY = 0.f;			// 상동
	
	_isGround = true;		//땅 위에 있는가? 아이템은 맨 처음 땅 위에 있기에 true
	itemAttack = false;
}

void Item::Update()
{
	if (itemAttack)
	{
		if (animator->currentFrame == 5)
		{
			ItemAttack();
		}
	}
	if (_speedX != 0)
	{
		ItemThrowAttack();
	}
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
	
	if (_isGround == false)					//땅 위에 있지 않다면
	{
		transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());
		_speedY += _gravity * TIMEMANAGER->getElapsedTime();
	}

	if (_isGround == true)					//throw해서 땅 위에 착지 한다면 마찰력 부여
	{
		if (_throwDir == false)				    //right일때 마찰력
		{
			_speedX -= _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX <= 0) _speedX = 0;
		}

		if (_throwDir == true)				//left일때 마찰력
		{
			_speedX += _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX >= 0) _speedX = 0;
		}
	}
	//땅에 착지 시
	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= _itemZ && _itemZ != 0)
	{
		_speedY = 0.0f;
		_isGround = true;
	}

	//item이 MainCam의 범위 초과시
	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 <= transform->GetX())
	{
		_speedX *= -1;					//범위 초과시 x 좌표 방향 바꿔줌		
	}
}
void Item::Render()
{
}

void Item::SetItemImage(string imageName)
{
	animator->AddClip(imageName, CLIPMANAGER->FindClip(imageName));
	animator->SetClip(imageName);
}

void Item::ItemAttack()
{
	itemAttack = false;
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_sectorEnemyV[i]->isActive == false) continue;

		float _distance = GetDistance(transform->GetX(), transform->gameObject->GetComponent<ZOrder>()->GetZ(),
			_sectorEnemyV[i]->transform->GetX(),
			_sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ());

		if (_distance < 100) 
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(10);
			EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX(), transform->GetY());
		}
	}
}

void Item::ItemThrowAttack()
{
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_isHitThrow[i] == true) continue;
		if (_sectorEnemyV[i]->isActive == false) continue;

		float _distance = GetDistance(transform->GetX(), transform->gameObject->GetComponent<ZOrder>()->GetZ(),
			_sectorEnemyV[i]->transform->GetX(),
			_sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ());

		if (_distance < 100)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(10);
			_isHitThrow[i] = true;
			EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX(), transform->GetY());
			_speedX *= -1;
		}
	}
}

void Item::Throw(bool dir)			//throw시 bool값 dir 반환
{
	_throwDir = dir;	
	_isGround = false;
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	_isHitThrow.clear();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		_isHitThrow.push_back(false);
	}
	if (dir == false)				// right일때
	{
		_angle = 0;
	}
	if (dir == true)				// left일때
	{
		_angle = PI;
	}

	_speedX = cosf(_angle) * _itemSpeed;
	_speedY = -sinf(_angle) * _itemSpeed;
}

void Item::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		animator->SetClip(animator->GetClip(clipName));
	}
	else
	{
		animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
	}
}
