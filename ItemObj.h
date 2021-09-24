#pragma once
#include "GameObject.h"

class ItemObj :
	public GameObject
{
private:

public:

	Animator* animator;
	Renderer* renderer;
	BoxCollider* collider;
	Item* item;

	virtual void Init();
};

