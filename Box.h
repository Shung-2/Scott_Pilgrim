#pragma once
#include "GameObject.h"
class Box :
    public GameObject
{
public:
    Box();
    ~Box();
    Renderer* renderer;
    BoxCollider* collider;
};

