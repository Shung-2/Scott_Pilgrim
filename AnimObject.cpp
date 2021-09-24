#include "stdafx.h"
#include "AnimObject.h"

AnimObject::AnimObject()
{
	renderer = new Renderer();
	AddComponent(renderer);
	renderer->Init();

	animator = new Animator();
	AddComponent(animator);
	animator->Init();
}

AnimObject::~AnimObject()
{
}

void AnimObject::Init()
{
}

void AnimObject::Update()
{
	GameObject::Update();
}

void AnimObject::Render()
{
	GameObject::Render();
}

void AnimObject::AddAnimationClip(string clipName, AnimationClip* newClip)
{
	animator->AddClip(clipName, newClip);
}
