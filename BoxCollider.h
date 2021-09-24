#pragma once
#include "Component.h"
class BoxCollider :
    public Component
{
public:
    BoxCollider();
    ~BoxCollider();
    vector<int> vCol;
    vector<int> prevCol;
    bool isTrigger;
    int width;
    int height;
    int weight;
    virtual void Update();
    virtual void Render();
    virtual void OnDisable();
    virtual void OnEnable();
    bool CheckCollision(float tempX, float tempY);
    bool CheckCollision(float tempX, float tempY, int colIdx);
    bool CheckCollision(RECT rc, int colIdx);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetSize(int width, int height);
    RECT rc;
    RECT intersectRc;
};

