#pragma once
#include "BoxCollider.h"
class ColliderManager : public singletonBase<ColliderManager>
{
public:
	vector<BoxCollider*> colliderList;
	ColliderManager();
	~ColliderManager();
	HRESULT Init();
	void Release();
	void EraseCollider(BoxCollider* targetCollider);
	void AddCollider(BoxCollider* newCollider);
};

