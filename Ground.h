#pragma once
#include "Component.h"

class ZOrder;

class Ground :
    public Component
{
private:
    RECT _rc;
    float _x;
    float _y;
    float _z;
    int _deltaX;
    int _deltaY;
    int _width;
    int _height;
public:
    virtual void Init();
    virtual void Init(int width, int height, int deltaX, int deltaY);
    virtual void Update();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();

    bool CheckWallCross(float nextX, float nextY);
    void Move(float x, float y);
    void MoveX(float x);
    void MoveY(float y);
    void ReSize(int width, int height);
    
    void SetX(float x) { _x = x; }
    float GetX() const { return _x; }

    void SetY(float y) { _y = y; }
    float GetY() const { return _y; }

    float GetZ() const { return _z; }

    RECT GetRc() { return _rc; }
};

