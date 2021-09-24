#pragma once
#include <vector>
#include "CameraControler.h"
class Player;
using namespace std;

#define SECTOR_NUM 5

#define TYPE_NUM 8

#define LUKE 0
#define DOBERMAN 1
#define MALCOLM 2
#define WILLIAM 3
#define JESSE 4
#define MIKE 5
#define LEE 6
#define RICHARD 7
class EnemyManager : public singletonBase<EnemyManager>
{
private:
	typedef int TYPE;
private:
	int _curSector;
	int _spawnPointV[SECTOR_NUM];
	bool _isActiveSector[SECTOR_NUM];
	vector<GameObject*> _enemyV[TYPE_NUM];
	vector<GameObject*> _sectorEnemyV;
	vector<pair<TYPE, int>> _sectorEnemyIdxV[SECTOR_NUM];
	Transform* _playerTr;
	Player* _playerComponent;
	CameraControler* _cameraControler;
public:
	HRESULT Init();
	void Update();
	void Render();
	void Release();

	vector<GameObject*>* GetEnemyVAddress(int type) { return &(_enemyV[type]); }
	vector<GameObject*> GetSectorEnemy();
	bool IsClearSector();

	int GetSectorNum() const { return _curSector; }
	void SetSectorNum(int sectorNum) { _curSector = sectorNum; }

	void SetPlayerTransform(GameObject* player);
	void SetCameraControler(CameraControler* cameraControler) { _cameraControler = cameraControler; }

	void Clear();
	void MakeSectorEnemyV();

	void DeadEvent(GameObject* deadObject);

	void InitSectorEnemyIdx();
};

