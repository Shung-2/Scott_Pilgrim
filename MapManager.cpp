#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::Init()
{
    sinkholeStartX = 2940;
    sinkholeEndX = 3340;
    sinkholeStartZ = 380;
    sinkholeEndZ = 568;

    slopeStartX1 = 16920;
    slopeEndX1 = 17240;
    slopeStartZ1 = 380;
    slopeEndZ1 = 800;

    slopeStartX2 = 18900;
    slopeEndX2 = 19175;
    slopeStartZ2 = 380;
    slopeEndZ2 = 600;

    slopeAngle1 = PI / 3;
    return S_OK;
}

void MapManager::Update()
{
    for (int i = 0; i < enemyV->size(); i++)
    {
        if ((*enemyV)[i]->transform->GetX() >= sinkholeStartX && 
            (*enemyV)[i]->transform->GetX() <= sinkholeEndX && 
            (*enemyV)[i]->GetComponent<ZOrder>()->GetZ() >= sinkholeStartZ && 
            (*enemyV)[i]->GetComponent<ZOrder>()->GetZ() <= sinkholeEndZ)
        {
            (*enemyV)[i]->GetComponent<ZOrder>()->SetZ(1000);
        }
    }

    if (player->transform->GetX() >= sinkholeStartX &&
        player->transform->GetX() <= sinkholeEndX &&
        player->GetComponent<ZOrder>()->GetZ() >= sinkholeStartZ &&
        player->GetComponent<ZOrder>()->GetZ() <= sinkholeEndZ)
    {
        player->GetComponent<ZOrder>()->SetZ(1000);
    }
}

void MapManager::Release()
{
}

bool MapManager::IsInSlope1(GameObject* gameObject)
{
    if (gameObject->transform->GetX() >= slopeStartX1 &&
        gameObject->transform->GetX() <= slopeEndX1 &&
        gameObject->GetComponent<ZOrder>()->GetZ() >= slopeStartZ1 &&
        gameObject->GetComponent<ZOrder>()->GetZ() <= slopeEndZ1)
    {
        return true;
    }
    return false;
}
