#include "stdafx.h"
#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

HRESULT ColliderManager::Init()
{
	return S_OK;
}

void ColliderManager::Release()
{
	colliderList.clear();
}

void ColliderManager::EraseCollider(BoxCollider* targetCollider)
{
	for (int i = 0; i < colliderList.size(); i++) {
		if (colliderList[i] == targetCollider) {
			colliderList.erase(colliderList.begin() + i);
			break;
		}
	}
}

void ColliderManager::AddCollider(BoxCollider* newCollider)
{
	colliderList.push_back(newCollider);
}
