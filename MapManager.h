#pragma once
class MapManager : public singletonBase<MapManager>
{
private:
    int sinkholeStartX;
    int sinkholeEndX;
    int sinkholeStartZ;
    int sinkholeEndZ;

    int slopeStartX1;
    int slopeEndX1;
    int slopeStartZ1;
    int slopeEndZ1;

    int slopeStartX2;
    int slopeEndX2;
    int slopeStartZ2;
    int slopeEndZ2;
public:
    float slopeAngle1;
    GameObject* player;
    vector<GameObject*>* enemyV;
    HRESULT Init();
    void Update();
    void Release();

    bool IsInSlope1(GameObject* gameObject);
};

