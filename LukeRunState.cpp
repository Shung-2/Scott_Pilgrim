#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeWalkState.h"
#include "LukeRunState.h"
#include "LukeAttack1State.h"
#include "LukeKickState.h"

EnemyState* LukeRunState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("luke_run_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("luke_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* RUN ���� �� PLAYER�� ������ ��� ��� */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new LukeIdleState();
	}

	/* RUN ���� �� PLAYER ���� �� ������, Z�൵ ������ ���� ������� ��� */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 100 &&
		enemy->zOrder->GetZ() - 6 <= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() &&
		enemy->zOrder->GetZ() + 6 >= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ())
	{
		/* �޺����� OR ������ ���� �� �������� */
		int randomAttack = RND->getInt(2);
		switch (randomAttack)
		{
		case 0:
			return new LukeAttack1State();
		case 1:
			return new LukeKickState();
		}
	}

	/* 210730 �����丵 by �뿵 */
	_runningTime += TIMEMANAGER->getElapsedTime();
	if (_runningTime >= _runLimitTime)
	{
		return new LukeIdleState();
	}
	else
	{
		enemy->transform->MoveX(_speed * TIMEMANAGER->getElapsedTime() * cosf(_runAngle));
		enemy->zOrder->MoveZ(_speed * TIMEMANAGER->getElapsedTime() * -sinf(_runAngle));

		// Y�� ����
		if (_runFlag == 1 && 
			enemy->zOrder->GetZ() <= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() + 1 &&
			enemy->zOrder->GetZ() >= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() - 1)
			//�����̵��� ���
		{
			return new LukeIdleState();
		}
	}

	return nullptr;
}

void LukeRunState::Enter(EnemyAI* enemy)
{
	/* 210730 �����丵 by �뿵
	1. X��, Y�� ������
	2.�������� ������ ���� (X, Y, �밢��) */

	_runFlag = RND->getInt(3);		// switch ���� ����ϱ� ���� Flag ����
	_runningTime = 0.f;				// ���� �ð�
	_runLimitTime = 2.f;			// ���� ���� �ð�
	
	switch (_runFlag)
	{
	case 0: // X��
		if (enemy->enemyinfo->GetDir() == false)
			_runAngle = 0;
		else
			_runAngle = PI;
		break;
		
	case 1: // Y��
		if (enemy->zOrder->GetZ() < enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ())
			_runAngle = PI * 3 / 2;
		else
			_runAngle = PI / 2;
		break;

	case 2: // �밢��
		_runAngle = GetAngle(enemy->transform->GetX(), enemy->zOrder->GetZ(),
			enemy->GetPlayerTransform()->GetX(), enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ());
		break;
	}

	/* �ȴ� �ӵ��� �ٴ� �ӵ��� �ٸ��Ƿ�, �ӵ� * 1.5 ���� */
	_speed = enemy->enemyinfo->GetSpeed() * 1.5;

	/* 210730 �����丵 by �뿵
	1. Enemy�� ���°� ���� ���� ���������� ���� ��� 
	-> ���ʹ� Attack ���� ��� ��� ������ "Luke", "Jesse" ���� �Ʒ��� ���� �־��ش�. */
	char clipName[32];
	if (enemy->enemyinfo->GetDir() == false)
	{
		sprintf_s(clipName, "%s_run_right", enemy->enemyinfo->GetName().c_str());
		enemy->ChangeClip(clipName, true);
	}
	else
	{
		sprintf_s(clipName, "%s_run_left", enemy->enemyinfo->GetName().c_str());
		enemy->ChangeClip(clipName, true);
	}
	//-------------------------------------------------------------------------------
}

void LukeRunState::Exit(EnemyAI* enemy)
{

}