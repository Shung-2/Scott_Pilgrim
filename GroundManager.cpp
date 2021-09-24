#include "stdafx.h"
#include "GroundManager.h"
#include "Ground.h"
HRESULT GroundManager::Init()
{
    return S_OK;
}

void GroundManager::Release()
{
    _groundV.clear();
}

void GroundManager::AddGround(Ground* newGround)
{
    _groundV.push_back(newGround);
}

void GroundManager::EraseGround(Ground* targetGround)
{
    for (int i = 0; i < _groundV.size(); i++) 
    {
        if (targetGround == _groundV[i]) 
        {
            _groundV.erase(_groundV.begin() + i);
            break;
        }
    }
}

int GroundManager::CheckGround(float x, float y, float z, int width, int height)
{
    for (int i = 0; i < _groundV.size(); i++) 
    {
        int intersectHeight = CheckGround(x, y, z, width, height, i);
        if (intersectHeight != 0)
        {
            return intersectHeight;
        }
    }
    return 0;
}

int GroundManager::CheckGround(RECT rc, float z)
{
    for (int i = 0; i < _groundV.size(); i++)
    {
        int intersectHeight = CheckGround(rc, z, i);
        if (intersectHeight != 0)
        {
            return intersectHeight;
        }
    }
    return 0;
}

int GroundManager::CheckGround(float x, float y, float z, int width, int height, int idx)
{
    RECT intersectRc;
    RECT destRc = RectMakeCenter(x, y, width, height);
    if (z <= _groundV[idx]->GetZ() - 5 || z >= _groundV[idx]->GetZ() + 5)
        return 0;
    if (IntersectRect(&intersectRc, &destRc, &_groundV[idx]->GetRc())) {
        return intersectRc.bottom - intersectRc.top;
    }
    return 0;
}

int GroundManager::CheckGround(RECT rc, float z, int idx)
{
    RECT intersectRc;
    if (z <= _groundV[idx]->GetZ() - 5 || z >= _groundV[idx]->GetZ() + 5)
        return 0;
    if (IntersectRect(&intersectRc, &rc, &_groundV[idx]->GetRc())) {
        return intersectRc.bottom - intersectRc.top;
    }
    return 0;
}

RECT GroundManager::GetGroundRect(int idx)
{
    return _groundV[idx]->GetRc();
}
