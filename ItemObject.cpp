#include "stdafx.h"
#include "ItemObject.h"

void ItemObject::Init()
{
	renderer = new Renderer();
	AddComponent(renderer);
	renderer->Init();

	animator = new Animator();
	AddComponent(animator);
	animator->Init();

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
	collider->isTrigger = true;

	zorder = new ZOrder();
	AddComponent(zorder);
	zorder->Init();

	item = new Item();
	AddComponent(item);
	item->Init();

}
