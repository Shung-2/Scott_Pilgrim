#include "stdafx.h"
#include "EditorScene.h"
#include "Outline.h"
#include <string>

EditorScene::EditorScene()
{
}

EditorScene::~EditorScene()
{
}

HRESULT EditorScene::Init()
{
    Scene::Init();
    HDC hdc = GetDC(_hWnd);
    HBITMAP hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
    backDC = CreateCompatibleDC(hdc);
    SelectObject(backDC, hBit);
    DeleteObject(hBit);
    ReleaseDC(_hWnd, hdc);

    for (int i = 0; i < TYPE_NUM; i++)
    {
		_sceneInfoLoader.SetLinkObjectVAddress(&_objectV[i]);
		_sceneInfoLoader.LoadObjectInfo(i);
    }
    for (int i = 0; i < TYPE_NUM; i++)
    {
		for (int j = 0; j < _objectV[i].size(); j++)
		{
			OBJECTNAME objectName;
			objectName.name = _objectV[i][j]->name;
			objectName.rc = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * j, NAME_WIDTH, NAME_HEIGHT);
			_objectNameV[i].push_back(objectName);
		}
    }
    _mouseDeltaX = 0;
    _mouseInfo.clickedLeft = false;
    _mouseInfo.clickedRight = false;
    _mouseInfo.deltaX = 0;
    _mouseInfo.deltaY = 0;
    _mouseInfo.preX = 0;
    _mouseInfo.preY = 0;
    
    _selectIdxType = -1; 
    _selectIdxObject = -1;
    _selectIdxName = 0;
    _selectIdxNameType = 0;
    _selectIdxMenu = 0;
    _clickScreen = false;
    _isWallMode = false;

    InitTypeName();
    InitObjectMenu();
    InitButton();
    OutlineInit();
    BackgroundInit();
    CameraInit();
    return S_OK;
}

void EditorScene::Release()
{
}

void EditorScene::Update()
{
    BGMANAGER->Update();
    ZORDER->Update();
    if (!KEYMANAGER->isToggleKey(VK_SHIFT))
        _outline.GetComponent<Renderer>()->enable = false;
    else
        _outline.GetComponent<Renderer>()->enable = true;
    _outline.Update();
    sprintf_s(debug[0], "%d", _selectIdxName);
    for (int i = 0; i < TYPE_NUM; i++)
    {
		for (int j = 0; j < _objectV[i].size(); j++)
		{
			_objectV[i][j]->Update();
		}
    }
    _selectNameRect = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * _selectIdxName, NAME_WIDTH, NAME_HEIGHT);
    //마우스를 클릭했을때 동작
    //1.월드를 클릭했을 경우
    //2.배치된 오브젝트를 클릭했을 경우
    //3.오브젝트 메뉴를 클릭했을 경우
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
        _isWallMode = !_isWallMode;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_mouseInfo.clickedLeft = true;
		_clickScreen = false;
		_selectIdxObject = -1;
		_selectIdxObjectType = -1;
		_selectIdxType = -1;
		_mouseInfo.preX = _ptMouse.x;
		_mouseInfo.preY = _ptMouse.y;

		//에디터 화면쪽을 클릭했을 때
		if (_ptMouse.x <= 650 && _ptMouse.y <= 400)
		{
			_clickScreen = true;
			POINT worldPtMouse = ScreenToWorld(_ptMouse.x, _ptMouse.y);

			//배치된 오브젝트를 클릭했을 때
			for (int i = 0; i < TYPE_NUM; i++)
			{
				for (int j = 0; j < _objectV[i].size(); j++) {
					if (PtInRect(&(_objectV[i][j]->GetComponent<Renderer>()->GetRc()), worldPtMouse)) {
						if (KEYMANAGER->isStayKeyDown(VK_MENU))
						{
							RemoveObject(i, j);
						}
						else
						{
							_clickScreen = false;
							_selectIdxObjectType = i;
							_selectIdxNameType = i;
							_selectIdxObject = j;
							_selectIdxName = j;
							SetOutline(_objectV[i][j]);
							break;
						}
					}
				}
			}
		}
		else
		{
			//오브젝트 메뉴를 클릭했을때
			for (int i = _selectIdxMenu * 5; i < _selectIdxMenu * 5 + 5; i++)
			{
				if (i == TYPE_NUM) break;
				if (PtInRect(&_objectMenu[i].rc, _ptMouse))
				{
					_selectIdxType = i;
					_selectObject.deltaX = _ptMouse.x - _objectMenu[i].x;
					_selectObject.deltaY = _ptMouse.y - _objectMenu[i].y;
					_selectObject.width = _objectMenu[i].img->getWidth() * _worldEditorRatio;
					_selectObject.height = _objectMenu[i].img->getHeight() * _worldEditorRatio;
					_selectObject.img = _objectMenu[i].img;
					break;
				}
			}
			//오브젝트 이름을 클릭했을 때
			for (int j = 0; j < _objectNameV[_selectIdxNameType].size(); j++)
			{
				if (PtInRect(&_objectNameV[_selectIdxNameType][j].rc, _ptMouse))
				{
					ClickObjectName(j);
					SetOutline(_objectV[_selectIdxNameType][j]);
					break;
				}
			}

			//이름 타입 네비게이션 버튼을 눌렀을 때
			{
				if (PtInRect(&_nameBeforeButton.rc, _ptMouse) && _selectIdxNameType != 0)
				{
					_selectIdxNameType--;
					if (_objectV[_selectIdxNameType].empty() == false)
					{
						SetOutline(_objectV[_selectIdxNameType][0]);
						ClickObjectName(0);
					}
					else
						_selectIdxName = -1;
				}
				if (PtInRect(&_nameNextButton.rc, _ptMouse) && _selectIdxNameType != TYPE_NUM - 1)
				{
					_selectIdxNameType++;
					if (_objectV[_selectIdxNameType].empty() == false)
					{
						SetOutline(_objectV[_selectIdxNameType][0]);
						ClickObjectName(0);
					}
					else
						_selectIdxName = -1;
				}
			}

			//오브젝트 메뉴 네비게이션 버튼을 눌렀을 때
			{
				if (PtInRect(&_menuBeforeButton.rc, _ptMouse) && _selectIdxMenu != 0)
				{
					_selectIdxMenu--;
				}
				if (PtInRect(&_menuNextButton.rc, _ptMouse) && _selectIdxMenu != (TYPE_NUM - 1) / 5)
				{
					_selectIdxMenu++;
				}
			}
		}
	}

    //마우스가 클릭된채로 움직일때 동작
    if (_mouseInfo.clickedLeft == true) 
    {
        _mouseInfo.deltaX = _ptMouse.x - _mouseInfo.preX;
        _mouseInfo.deltaY = _ptMouse.y - _mouseInfo.preY;
        if (_clickScreen == true)
        {
            MoveScreen();
        }
        else if (_selectIdxObject != -1)
        {
            _objectV[_selectIdxObjectType][_selectIdxObject]->transform->MoveX(_mouseInfo.deltaX / _worldEditorRatio);
            _objectV[_selectIdxObjectType][_selectIdxObject]->GetComponent<ZOrder>()->MoveZ(_mouseInfo.deltaY / _worldEditorRatio);
            _outline.transform->MoveX(_mouseInfo.deltaX / _worldEditorRatio);
            _outline.GetComponent<ZOrder>()->MoveZ(_mouseInfo.deltaY / _worldEditorRatio);
        }
        else if(_selectIdxType != -1)
        {
            _selectObject.x = _ptMouse.x - _selectObject.deltaX;
            _selectObject.y = _ptMouse.y - _selectObject.deltaY;
            _selectObject.rc = RectMakeCenter(_selectObject.x, _selectObject.y, _selectObject.width, _selectObject.height);
        }
        _mouseInfo.preX = _ptMouse.x;
        _mouseInfo.preY = _ptMouse.y;
    }

    //마우스를 뗐을때 동작
    //클릭했을 때 무엇을 클릭했느냐에 따라 다르게 동작
    if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        _mouseInfo.clickedLeft = false;

        //오브젝트 메뉴를 클릭했을 경우 마우스를 뗐을 때 배치된 오브젝트 벡터에 오브젝트 추가
        if (_selectIdxType != -1 && _ptMouse.x <= 650 && _ptMouse.y <= 400) 
        {
            GameObject* newObject;
            OBJECTNAME newObjectName;
			POINT worldPoint = ScreenToWorld(_selectObject.x, _selectObject.y);
            switch (_selectIdxType) {
            case 0:
                newObject = _sceneInfoLoader.MakeSnow1(worldPoint.x, worldPoint.y);
                break;
            case 1:
                newObject = _sceneInfoLoader.MakeSnow2(worldPoint.x, worldPoint.y);
                break;
            case 2:
                newObject = _sceneInfoLoader.MakeFencePillar(worldPoint.x, worldPoint.y);
                break;
            case 3:
                newObject = _sceneInfoLoader.MakeFencePillar2(worldPoint.x, worldPoint.y);
                break;
            case 4:
                newObject = _sceneInfoLoader.MakeGuardRail(worldPoint.x, worldPoint.y);
                break;
            case 5:
                newObject = _sceneInfoLoader.MakeFirePlug(worldPoint.x, worldPoint.y);
                break;
            case 6:
                newObject = _sceneInfoLoader.MakeHorse1(worldPoint.x, worldPoint.y);
                break;
            case 7:
                newObject = _sceneInfoLoader.MakeHorse2(worldPoint.x, worldPoint.y);
                break;
            case 8:
                newObject = _sceneInfoLoader.MakePostbox(worldPoint.x, worldPoint.y);
                break;
            case 9:
                newObject = _sceneInfoLoader.MakeShovel(worldPoint.x, worldPoint.y);
                break;
            case 10:
                newObject = _sceneInfoLoader.MakeSignBoard(worldPoint.x, worldPoint.y);
                break;
            case 11:
                newObject = _sceneInfoLoader.MakeWell(worldPoint.x, worldPoint.y);
                break;
            case 12:
                newObject = _sceneInfoLoader.MakeWood(worldPoint.x, worldPoint.y);
                break;
            case 13:
                newObject = _sceneInfoLoader.MakeLukeEditor(worldPoint.x, worldPoint.y);
                break;
            case 14:
                newObject = _sceneInfoLoader.MakeDobermanEditor(worldPoint.x, worldPoint.y);
                break;
            case 15:
                newObject = _sceneInfoLoader.MakeMalcolmEditor(worldPoint.x, worldPoint.y);
                break;
            case 16:
                newObject = _sceneInfoLoader.MakeWilliamEditor(worldPoint.x, worldPoint.y);
                break;
            case 17:
                newObject = _sceneInfoLoader.MakeJesseEditor(worldPoint.x, worldPoint.y);
                break;
            case 18:
                newObject = _sceneInfoLoader.MakeMikeEditor(worldPoint.x, worldPoint.y);
                break;
            case 19:
                newObject = _sceneInfoLoader.MakeLeeEditor(worldPoint.x, worldPoint.y);
                break;
            case 20:
                newObject = _sceneInfoLoader.MakeRichardEditor(worldPoint.x, worldPoint.y);
                break;
            }
            _objectV[_selectIdxType].push_back(newObject);
            newObjectName.name = newObject->name;
            newObjectName.rc = RectMake(NAME_STARTX, NAME_STARTY + 20 * _objectNameV[_selectIdxType].size(), NAME_WIDTH, NAME_HEIGHT);
            _objectNameV[_selectIdxType].push_back(newObjectName);
            _selectIdxNameType = _selectIdxType;
            _selectIdxName = _objectV[_selectIdxType].size() - 1;
            SetOutline(newObject);
        }
		_selectIdxType = -1;
    }

    //배치된 오브젝트 정보들을 텍스트 데이터로 저장
    if (KEYMANAGER->isOnceKeyDown('S'))
    {
		vector<string> objectStringInfo;
        for (int i = 0; i < TYPE_NUM; i++)
        {
			for (int j = 0; j < _objectV[i].size(); j++)
			{
				objectStringInfo.push_back(to_string(_objectV[i][j]->transform->GetX()));
				objectStringInfo.push_back(to_string(_objectV[i][j]->transform->GetY()));
				objectStringInfo.push_back(to_string(i));
			}
        }
		TXTDATAMANAGER->txtSave("scene_info.txt", objectStringInfo);
    }
}

void EditorScene::Render()
{
    PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
    BGMANAGER->Render();
    ZORDER->Render();
    MainCam->Render(backDC);

    //오브젝트 메뉴 렌더링
    for (int i = _selectIdxMenu * 5; i < _selectIdxMenu * 5 + 5; i++)
    {
        if (i == TYPE_NUM) break;
		GdiTransparentBlt(backDC, 
            _objectMenu[i].rc.left, _objectMenu[i].rc.top, 
            _objectMenu[i].width, _objectMenu[i].height, 
            _objectMenu[i].img->getMemDC(),
            0, 0, 
            _objectMenu[i].img->getWidth(),
            _objectMenu[i].img->getHeight(),
            RGB(255, 0, 255));
    }
    
    //선택렉트 렌더링
    DrawSelectRect();
    SetBkMode(backDC, TRANSPARENT);

    //오브젝트 타입 이름 렌더링
    TextOut
    (
        backDC, NAME_STARTX, NAME_STARTY - 20, 
        _typeNameArr[_selectIdxNameType].c_str(), 
        strlen(_typeNameArr[_selectIdxNameType].c_str())
    );

    //오브젝트 이름 목록 렌더링
    for (int i = 0; i < _objectNameV[_selectIdxNameType].size(); i++)
    {
        TextOut
        (
            backDC, NAME_STARTX, NAME_STARTY + NAME_HEIGHT * i,
            _objectNameV[_selectIdxNameType][i].name.c_str(), 
            strlen(_objectNameV[_selectIdxNameType][i].name.c_str())
        );
    }

    //드래그중인 오브젝트 렌더링
    if (_selectIdxType != -1)
    {
        GdiTransparentBlt(backDC,
            _selectObject.rc.left,
            _selectObject.rc.top,
            _selectObject.width,
            _selectObject.height,
            _selectObject.img->getMemDC(),
            0, 0,
            _selectObject.img->getWidth(),
            _selectObject.img->getHeight(),
            RGB(255, 0, 255));
    }

    //버튼 렌더링
    {
        if(_selectIdxNameType != 0)
            _nameBeforeButton.img->render(backDC, _nameBeforeButton.rc.left, _nameBeforeButton.rc.top);
        if(_selectIdxNameType != TYPE_NUM - 1)
            _nameNextButton.img->render(backDC, _nameNextButton.rc.left, _nameNextButton.rc.top);
        if (_selectIdxMenu != 0)
            _menuBeforeButton.img->render(backDC, _menuBeforeButton.rc.left, _menuBeforeButton.rc.top);
        if (_selectIdxMenu != (TYPE_NUM - 1) / 5)
            _menuNextButton.img->render(backDC, _menuNextButton.rc.left, _menuNextButton.rc.top);
    }

    sprintf_s(debug[1], "%.1f, %.1f", _ptMouse.x / _worldEditorRatio, _ptMouse.y / _worldEditorRatio);
    if (!KEYMANAGER->isToggleKey(VK_TAB))
    {
		TextOut(backDC, 20, 20, debug[0], strlen(debug[0]));
		TextOut(backDC, _ptMouse.x, _ptMouse.y - 20, debug[1], strlen(debug[1]));
    }
    BitBlt(_hdc, 0, 0, WINSIZEX, WINSIZEY, backDC, 0, 0, SRCCOPY);
}

void EditorScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) 
    {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
        _background[i] = new ImageObject();
        _background[i]->renderer->Init(fileName, 922, 680);
        _background[i]->transform->SetPosition(922 * i + 922 / 2, 680 / 2);
        _background[i]->name = "background";
        BGMANAGER->AddBackground(_background[i]);
    }
    BGMANAGER->SetMargin(30);
    BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(MainCam->transform);
}

void EditorScene::CameraInit()
{
    _mapWidth = 21206;
    _mapHeight = 680;
    _worldEditorRatio = 0.75f;
    _editorWidth = WINSIZEX * _worldEditorRatio;
    _editorHeight = WINSIZEY * _worldEditorRatio;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    MainCam->SetScreenSize(_editorWidth, _editorHeight);
    SetBackBufferSize(_mapWidth, _mapHeight);
}

RECT EditorScene::WorldToScreen(RECT rc)
{
    //실제 월드의 렉트를 에디터 스크린상의 렉트로 전환.
    //left,top을 구해서 width , height로 RectMake하기
    POINT leftTop = WorldToScreen(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, (rc.right - rc.left) * _worldEditorRatio, (rc.bottom - rc.top) * _worldEditorRatio);
    return result;
}

RECT EditorScene::ScreenToWorld(RECT rc)
{
    POINT leftTop = ScreenToWorld(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, rc.right - rc.left, rc.bottom - rc.top);
    return result;
}

POINT EditorScene::WorldToScreen(long x, long y)
{
    //월드좌표를 에디터상 화면 좌표로 변환
    long resultX = (x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2)) * _worldEditorRatio;
    long resultY = y * _worldEditorRatio;

    return { resultX, resultY };
}

POINT EditorScene::ScreenToWorld(long x, long y)
{
    //에디터상의 좌표를 월드좌표로 변환
    //드래그되는 오브젝트의 실제 월드좌표 공식 = camera.x - (WINSIZEX/2 - ptMouse.x / ratio)
    long resultX = MainCam->transform->GetX() - (WINSIZEX / 2 - x / _worldEditorRatio);
    long resultY = y / _worldEditorRatio;
    return{ resultX ,resultY };
}

void EditorScene::InitObjectMenu()
{
    for (int i = 0; i < TYPE_NUM; i++)
    {
        _objectMenu[i].img = new image();
        _objectMenu[i].x = OBJECT_MENU_STARTX + OBJECT_MENU_TERM * (i % 5);
        _objectMenu[i].y = OBJECT_MENU_STARTY;
        _objectMenu[i].type = i;
    }

    _objectMenu[0].img->init("map/snow1.bmp", 108, 44, true, RGB(255, 0, 255));
    _objectMenu[0].width = 80;
    _objectMenu[0].height = 44;
    _objectMenu[0].rc = RectMakeCenter(_objectMenu[0].x, _objectMenu[0].y, _objectMenu[0].width, _objectMenu[0].height);

    _objectMenu[1].img->init("map/snow2.bmp", 164, 62, true, RGB(255, 0, 255));
    _objectMenu[1].width = 80;
    _objectMenu[1].height = 50;
    _objectMenu[1].rc = RectMakeCenter(_objectMenu[1].x, _objectMenu[1].y, _objectMenu[1].width, _objectMenu[1].height);

    _objectMenu[2].img->init("map/fence_pillar.bmp", 114, 168, true, RGB(255, 0, 255));
    _objectMenu[2].width = 80;
    _objectMenu[2].height = 100;
    _objectMenu[2].rc = RectMakeCenter(_objectMenu[2].x, _objectMenu[2].y, _objectMenu[2].width, _objectMenu[2].height);

    _objectMenu[3].img->init("map/fence_pillar2.bmp", 114, 156, true, RGB(255, 0, 255));
    _objectMenu[3].width = 80;
    _objectMenu[3].height = 100;
    _objectMenu[3].rc = RectMakeCenter(_objectMenu[3].x, _objectMenu[3].y, _objectMenu[3].width, _objectMenu[3].height);

    _objectMenu[4].img->init("map/guardrail.bmp", 106, 112, true, RGB(255, 0, 255));
    _objectMenu[4].width = 70;
    _objectMenu[4].height = 72;
    _objectMenu[4].rc = RectMakeCenter(_objectMenu[4].x, _objectMenu[4].y, _objectMenu[4].width, _objectMenu[4].height);

	_objectMenu[5].img->init("map/fireplug.bmp", 98, 100, true, RGB(255, 0, 255));
	_objectMenu[5].width = 80;
	_objectMenu[5].height = 100;
	_objectMenu[5].rc = RectMakeCenter(_objectMenu[5].x, _objectMenu[5].y, _objectMenu[5].width, _objectMenu[5].height);

    _objectMenu[6].img->init("map/horse1.bmp", 110, 116, true, RGB(255, 0, 255));
    _objectMenu[6].width = 100;
    _objectMenu[6].height = 100;
    _objectMenu[6].rc = RectMakeCenter(_objectMenu[6].x, _objectMenu[6].y, _objectMenu[6].width, _objectMenu[6].height);

    _objectMenu[7].img->init("map/horse2.bmp", 106, 130, true, RGB(255, 0, 255));
    _objectMenu[7].width = 90;
    _objectMenu[7].height = 100;
    _objectMenu[7].rc = RectMakeCenter(_objectMenu[7].x, _objectMenu[7].y, _objectMenu[7].width, _objectMenu[7].height);

    _objectMenu[8].img->init("map/postbox.bmp", 74, 104, true, RGB(255, 0, 255));
    _objectMenu[8].width = 72;
    _objectMenu[8].height = 100;
    _objectMenu[8].rc = RectMakeCenter(_objectMenu[8].x, _objectMenu[8].y, _objectMenu[8].width, _objectMenu[8].height);

    _objectMenu[9].img->init("map/shovel.bmp", 52, 94, true, RGB(255, 0, 255));
    _objectMenu[9].width = 58;
    _objectMenu[9].height = 100;
    _objectMenu[9].rc = RectMakeCenter(_objectMenu[9].x, _objectMenu[9].y, _objectMenu[9].width, _objectMenu[9].height);

    _objectMenu[10].img->init("map/signboard.bmp", 108, 102, true, RGB(255, 0, 255));
    _objectMenu[10].width = 100;
    _objectMenu[10].height = 98;
    _objectMenu[10].rc = RectMakeCenter(_objectMenu[10].x, _objectMenu[10].y, _objectMenu[10].width, _objectMenu[10].height);

    _objectMenu[11].img->init("map/well.bmp", 106, 82, true, RGB(255, 0, 255));
    _objectMenu[11].width = 100;
    _objectMenu[11].height = 80;
    _objectMenu[11].rc = RectMakeCenter(_objectMenu[11].x, _objectMenu[11].y, _objectMenu[11].width, _objectMenu[11].height);

    _objectMenu[12].img->init("map/wood.bmp", 370, 74, true, RGB(255, 0, 255));
    _objectMenu[12].width = 96;
    _objectMenu[12].height = 24;
    _objectMenu[12].rc = RectMakeCenter(_objectMenu[12].x, _objectMenu[12].y, _objectMenu[12].width, _objectMenu[12].height);

    _objectMenu[13].img->init("luke/luke.bmp", 96, 128, true, RGB(255, 0, 255));
    _objectMenu[13].width = 80;
    _objectMenu[13].height = 100;
    _objectMenu[13].rc = RectMakeCenter(_objectMenu[13].x, _objectMenu[13].y, _objectMenu[13].width, _objectMenu[13].height);

    _objectMenu[14].img->init("doberman/doberman.bmp", 164, 96, true, RGB(255, 0, 255));
    _objectMenu[14].width = 100;
    _objectMenu[14].height = 65;
    _objectMenu[14].rc = RectMakeCenter(_objectMenu[14].x, _objectMenu[14].y, _objectMenu[14].width, _objectMenu[14].height);

    _objectMenu[15].img->init("malcolm/malcolm.bmp", 114, 159, true, RGB(255, 0, 255));
    _objectMenu[15].width = 71;
    _objectMenu[15].height = 100;
    _objectMenu[15].rc = RectMakeCenter(_objectMenu[15].x, _objectMenu[15].y, _objectMenu[15].width, _objectMenu[15].height);

    _objectMenu[16].img->init("william/william.bmp", 122, 146, true, RGB(255, 0, 255));
    _objectMenu[16].width = 84;
    _objectMenu[16].height = 100;
    _objectMenu[16].rc = RectMakeCenter(_objectMenu[16].x, _objectMenu[16].y, _objectMenu[16].width, _objectMenu[16].height);

    _objectMenu[17].img->init("jesse/jesse.bmp", 90, 132, true, RGB(255, 0, 255));
    _objectMenu[17].width = 68;
    _objectMenu[17].height = 100;
    _objectMenu[17].rc = RectMakeCenter(_objectMenu[17].x, _objectMenu[17].y, _objectMenu[17].width, _objectMenu[17].height);

    _objectMenu[18].img->init("mike/mike.bmp", 110, 134, true, RGB(255, 0, 255));
    _objectMenu[18].width = 82;
    _objectMenu[18].height = 100;
    _objectMenu[18].rc = RectMakeCenter(_objectMenu[18].x, _objectMenu[18].y, _objectMenu[18].width, _objectMenu[18].height);

    _objectMenu[19].img->init("lee/lee.bmp", 100, 132, true, RGB(255, 0, 255));
    _objectMenu[19].width = 76;
    _objectMenu[19].height = 100;
    _objectMenu[19].rc = RectMakeCenter(_objectMenu[19].x, _objectMenu[19].y, _objectMenu[19].width, _objectMenu[19].height);

    _objectMenu[20].img->init("richard/richard.bmp", 108, 132, true, RGB(255, 0, 255));
    _objectMenu[20].width = 82;
    _objectMenu[20].height = 100;
    _objectMenu[20].rc = RectMakeCenter(_objectMenu[20].x, _objectMenu[20].y, _objectMenu[20].width, _objectMenu[20].height);
}

void EditorScene::InitTypeName()
{
    _typeNameArr[0] = "Snow1";
    _typeNameArr[1] = "Snow2";
    _typeNameArr[2] = "fencePillar1";
    _typeNameArr[3] = "fencePillar2";
    _typeNameArr[4] = "guardrail";
    _typeNameArr[5] = "fireplug";
    _typeNameArr[6] = "horse1";
    _typeNameArr[7] = "horse2";
    _typeNameArr[8] = "postbox";
    _typeNameArr[9] = "shovel";
    _typeNameArr[10] = "signboard";
    _typeNameArr[11] = "well";
    _typeNameArr[12] = "wood";
    _typeNameArr[13] = "luke";
    _typeNameArr[14] = "doberman";
    _typeNameArr[15] = "malcolm";
    _typeNameArr[16] = "william";
    _typeNameArr[17] = "jesse";
    _typeNameArr[18] = "mike";
    _typeNameArr[19] = "lee";
    _typeNameArr[20] = "richard";
}

void EditorScene::InitButton()
{
    _nameNextButton.img = new image();
    _nameNextButton.img->init("ui/next.bmp", 25, 25, true, RGB(255, 0, 255));
    _nameNextButton.rc = RectMakeCenter(NAME_STARTX + NAME_WIDTH + 13, NAME_STARTY - 10, 26, 26);

    _nameBeforeButton.img = new image();
    _nameBeforeButton.img->init("ui/before.bmp", 25, 25, true, RGB(255, 0, 255));
    _nameBeforeButton.rc = RectMakeCenter(NAME_STARTX - 13, NAME_STARTY - 10, 26, 26);

    _menuNextButton.img = new image();
    _menuNextButton.img->init("ui/next.bmp", 25, 25, true, RGB(255, 0, 255));
    _menuNextButton.rc = RectMakeCenter(OBJECT_MENU_STARTX + OBJECT_MENU_TERM * 4 + 75, OBJECT_MENU_STARTY, 26, 26);

    _menuBeforeButton.img = new image();
    _menuBeforeButton.img->init("ui/before.bmp", 25, 25, true, RGB(255, 0, 255));
    _menuBeforeButton.rc = RectMakeCenter(OBJECT_MENU_STARTX - 75, OBJECT_MENU_STARTY, 26, 26);
}

void EditorScene::MoveScreen()
{
    if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
    {
        MainCam->transform->MoveX(-(_mouseInfo.deltaX * 3));
    }
    else
    {
        MainCam->transform->MoveX(-_mouseInfo.deltaX);
    }
    if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
        MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
}

void EditorScene::DrawSelectRect()
{
    if (_selectIdxName == -1) return;
    HBRUSH hBit, oBit;
    hBit = CreateSolidBrush(RGB(100, 100, 255));
    oBit = (HBRUSH)SelectObject(backDC, hBit);
    Rectangle(backDC, _selectNameRect);
    SelectObject(backDC, oBit);
    DeleteObject(hBit);
}

void EditorScene::ClickObjectName(int idx)
{
    _selectIdxName = idx;
    MainCam->transform->SetX(_objectV[_selectIdxNameType][_selectIdxName]->transform->GetX());
    if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
        MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
}

void EditorScene::OutlineInit()
{
    _outline.Init();
    _outline.AddComponent(new Renderer());
    _outline.GetComponent<Renderer>()->Init();
    _outline.AddComponent(new Outline());
    _outline.GetComponent<Outline>()->Init();
    _outline.AddComponent(new ZOrder());
    _outline.GetComponent<ZOrder>()->Init();

    if (_objectV[0].size() != 0)
    {
        SetOutline(_objectV[0][0]);
    }
}

void EditorScene::SetOutline(GameObject* targetObject)
{
    if (_outline.isActive == false)
        _outline.SetActive(true);
    _outline.transform->SetPosition(targetObject->transform->GetX(), targetObject->transform->GetY());
    _outline.GetComponent<Outline>()->SetTargetObject(targetObject);
    _outline.GetComponent<ZOrder>()->SetZ(targetObject->GetComponent<ZOrder>()->GetZ() - 1);
}

void EditorScene::RemoveObject(int objectType, int objectIdx)
{
    _objectV[objectType][objectIdx]->SetActive(false);
    SAFE_DELETE(_objectV[objectType][objectIdx]);
    _objectV[objectType].erase(_objectV[objectType].begin() + objectIdx);
    _objectNameV[objectType].erase(_objectNameV[objectType].begin() + objectIdx);
    for (int i = objectIdx; i < _objectNameV[objectType].size(); i++)
    {
        _objectNameV[objectType][i].rc = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * i, NAME_WIDTH, NAME_HEIGHT);
    }
    if (_selectIdxNameType == objectType && _selectIdxName == objectIdx)
    {
        _outline.SetActive(false);
        _selectIdxName = -1;
    }
    if (_selectIdxNameType == objectType && _selectIdxName > objectIdx)
    {
        _selectIdxName--;
    }
}

