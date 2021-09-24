#pragma once
#include "Scene.h"
#include "SceneInfoLoader.h"

#define BG_NUM 23
#define SNOW1 0
#define TYPE_NUM 21
#define NAME_STARTX 700
#define NAME_STARTY 50
#define NAME_WIDTH 150
#define NAME_HEIGHT 20

#define OBJECT_MENU_STARTX 100
#define OBJECT_MENU_STARTY 500
#define OBJECT_MENU_TERM 100
class EditorScene :
    public Scene
{
private:
    HDC backDC;
    typedef struct tagMouseInfo {
        float deltaX;
        float deltaY;
        bool clickedLeft;
        bool clickedRight;
        float preX;
        float preY;
        float clickX;
        float clickY;
        float releaseX;
        float releaseY;
    }MOUSEINFO;
    typedef struct tagObjectMenu {
        RECT rc;
        int x;
        int y;
        int width;
        int height;
        int type;
        image* img;
    }OBJECTMENU;
    typedef struct tagSelectObject {
        RECT rc;
        int deltaX;
        int deltaY;
        int width;
        int height;
        int x;
        int y;
        image* img;
    }SELECTOBJECT;

    typedef struct tagObjectNameButton {
        RECT rc;
        string name;
    }OBJECTNAME;

    typedef struct tagButton {
        RECT rc;
        image* img;
    }BUTTON;
private:
    bool _isWallMode;
    float _worldEditorRatio;
    float _editorWidth;
    float _editorHeight;
    SceneInfoLoader _sceneInfoLoader;
    vector<GameObject*> _objectV[TYPE_NUM];
    vector<OBJECTNAME> _objectNameV[TYPE_NUM];
    string _typeNameArr[TYPE_NUM];
    GameObject _outline;
    BUTTON _nameNextButton, _nameBeforeButton;
    BUTTON _menuNextButton, _menuBeforeButton;
    float _mouseDeltaX;
    int _selectIdxType;
    int _selectIdxObject;
    int _selectIdxObjectType;
    int _selectIdxName;
    int _selectIdxNameType;
    int _selectIdxMenu;
    bool _clickScreen;
    RECT _selectNameRect;
    ImageObject* _background[BG_NUM];
    OBJECTMENU _objectMenu[TYPE_NUM];
    SELECTOBJECT _selectObject;
    MOUSEINFO _mouseInfo;
public:
    EditorScene();
    ~EditorScene();
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
    void CameraInit();
    RECT WorldToScreen(RECT rc);
    RECT ScreenToWorld(RECT rc);
    POINT WorldToScreen(long x, long y);
    POINT ScreenToWorld(long x, long y);

    void InitObjectMenu();
    void InitTypeName();
    void InitButton();
    void MoveScreen();
    void DrawSelectRect();
    void ClickObjectName(int idx);
    void OutlineInit();
    void SetOutline(GameObject* targetObject);
    void RemoveObject(int objectType, int objectIdx);
};

