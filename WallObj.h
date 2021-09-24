#pragma once
#include "GameObject.h"
class Wall;
class WallObj :
    public GameObject
{
public:
    virtual void Init(int startX, int startY, int endX, int endY);
    Wall* wall;
};

