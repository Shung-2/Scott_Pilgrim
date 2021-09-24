#include "stdafx.h"
#include "UIBase.h"

UIBase::UIBase()
{
	uiRenderer = new UIRenderer();
	AddComponent(uiRenderer);
	uiRenderer->Init();
}

UIBase::~UIBase()
{
}

void UIBase::Init()
{
}

void UIBase::Update()
{
	GameObject::Update();
}

void UIBase::Render()
{
	GameObject::Render();
}
