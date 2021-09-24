#include "stdafx.h"
#include "HpUI.h"

void HpUI::Init(int mode)
{
	_mode = mode;
	uiRenderer = gameObject->GetComponent<UIRenderer>();
}

void HpUI::Update()
{
	int playerHp = playerInfo->hp;
	vector<int> _hpNumV;
	while (playerHp != 0)
	{
		int num = playerHp % 10;
		_hpNumV.push_back(num);
		playerHp /= 10;
	}
	if (_hpNumV.size() <= _mode)
	{
		gameObject->SetActive(false);
		return;
	}
	sprintf_s(filename, "ui/number%d.bmp", _hpNumV[_mode]);
	uiRenderer->Init(filename, 21, 30);
}

void HpUI::Render()
{

}
