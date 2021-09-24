#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//_hdc = GetDC(_hWnd);

	SetTimer(_hWnd, 1, 10, NULL);

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	//_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TAGMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->Init();
		COLLIDERMANAGER->Init();
		CAMERAMANAGER->Init();
		GROUNDMANAGER->Init();
		SOUNDMANAGER->init();
		TXTDATAMANAGER->Init();
		CLIPMANAGER->Init();
		BGMANAGER->Init();
		WALLMANAGER->Init();
		EFFECTMANAGER->Init();
		MAPMANAGER->Init();
		ENEMYMANAGER->Init();
		DAMAGEMANAGER->Init();
	}

	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	COLLIDERMANAGER->Release();
	COLLIDERMANAGER->releaseSingleton();

	CAMERAMANAGER->Release();
	CAMERAMANAGER->releaseSingleton();

	TAGMANAGER->release();
	TAGMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	SCENEMANAGER->Release();
	SCENEMANAGER->releaseSingleton();

	GROUNDMANAGER->Release();
	GROUNDMANAGER->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	TXTDATAMANAGER->release();
	TXTDATAMANAGER->releaseSingleton();

	CLIPMANAGER->Release();
	CLIPMANAGER->releaseSingleton();

	BGMANAGER->Release();
	BGMANAGER->releaseSingleton();

	WALLMANAGER->Release();
	WALLMANAGER->releaseSingleton();

	EFFECTMANAGER->Release();
	EFFECTMANAGER->releaseSingleton();

	MAPMANAGER->Release();
	MAPMANAGER->releaseSingleton();

	ENEMYMANAGER->Release();
	ENEMYMANAGER->releaseSingleton();

	DAMAGEMANAGER->Release();
	DAMAGEMANAGER->releaseSingleton();
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	//==================================================
	//���⵵ �ǵ�������
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //�� �� �߿��մ�...


	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
		break;
	
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			this->render(hdc);

			EndPaint(hWnd, &ps);
			break;
		}
		break;
		//���콺 �����̸� ���⼭ �޼��� �߻�
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;
			//���콺 ���� Ŭ��(�������� ������ ����)

		case WM_KEYDOWN:

			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			break;


			//������ â �ν���(?) 
		case WM_DESTROY:
		//������ �����Լ�
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}