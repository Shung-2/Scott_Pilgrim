#include "stdafx.h"
#include "Box.h"

Box::Box()
{
	renderer = new Renderer();
	AddComponent(renderer);
	renderer->Init();

	collider = new BoxCollider();
	AddComponent(collider);
	collider->Init();
}

Box::~Box()
{
}
