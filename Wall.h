#pragma once
#include "Component.h"
class Wall :
    public Component
{
private:
    float _startX;      //벽의 시작점
    float _startY;
    float _endX;        //벽의 끝점
    float _endY;
    float _gradient;    //벽의 기울기
    float _interceptY;  //벽의 y절편
public:
    virtual void Init(float startX, float startY, float endX, float endY);
    virtual void Update();
    virtual void Render();

    void SetStartPoint(float startX, float startY);
    void SetEndPoint(float endX, float endY);
    bool IsCross(float startX, float startY, float endX, float endY);
    int CalcUpDown(float x, float y);
    bool IsInLine(float x, float y);
};

