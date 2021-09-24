#include "stdafx.h"
#include "EnemyInfo.h"

void EnemyInfo::Init()
{

}

void EnemyInfo::Hit(int damage)
{
	_hp -= damage;
	//if (_hp <= 0)
	//{
	//	gameObject->SetActive(false);
	//	//TODO
	//	//dead;
	//}
}
