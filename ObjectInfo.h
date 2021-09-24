#pragma once
#include "Component.h"
class ObjectInfo :
    public Component
{
public:
    ObjectInfo(bool isAir);
    ~ObjectInfo();
    bool isAir;
};

