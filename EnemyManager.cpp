#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
HRESULT EnemyManager::Init()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		_isActiveSector[i] = false;
	}
	_spawnPointV[0] = 600;
	_spawnPointV[1] = 3000;
	_spawnPointV[2] = 5400;
	_spawnPointV[3] = 8000;
	_spawnPointV[4] = 10000;

	InitSectorEnemyIdx();
	_curSector = 0;
	return S_OK;
}

void EnemyManager::Update()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		if (_isActiveSector[i] == false && _playerTr->GetX() >= _spawnPointV[i])
		{
			MakeSectorEnemyV();
			for (int j = 0; j < _sectorEnemyV.size(); j++)
			{
				_sectorEnemyV[j]->SetActive(true);
			}
			_isActiveSector[i] = true;
		}
	}

	for (int i = 0; i < TYPE_NUM; i++)
	{
		for (int j = 0; j < _enemyV[i].size(); j++)
		{
			_enemyV[i][j]->Update();
		}
	}
}

void EnemyManager::Render()
{
}

void EnemyManager::Release()
{
}

vector<GameObject*> EnemyManager::GetSectorEnemy()
{
	return _sectorEnemyV;
}

bool EnemyManager::IsClearSector()
{
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		if (_enemyV[enemyType][enemyIdx]->isActive == true)
			return false;
	}

	_cameraControler->UnLock();
	return true;
}

void EnemyManager::SetPlayerTransform(GameObject* player)
{
	_playerTr = player->transform;
	_playerComponent = _playerTr->gameObject->GetComponent<Player>();
	for (int i = 0; i < TYPE_NUM; i++)
	{
		for (int j = 0; j < _enemyV[i].size(); j++)
		{
			_enemyV[i][j]->GetComponent<EnemyAI>()->SetPlayer(player);
		}
	}
}

void EnemyManager::Clear()
{
	_curSector++;
	_cameraControler->UnLock();
}

void EnemyManager::MakeSectorEnemyV()
{
	_sectorEnemyV.clear();
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		_sectorEnemyV.push_back(_enemyV[enemyType][enemyIdx]);
	}
}

void EnemyManager::DeadEvent(GameObject* deadObject)
{
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		if (_enemyV[enemyType][enemyIdx]->isActive == true)
			return;
	}
	Clear();
	return;
}

void EnemyManager::InitSectorEnemyIdx()
{
	_sectorEnemyIdxV[0].push_back({ 0, 0 });
	_sectorEnemyIdxV[0].push_back({ 5, 0 });
	
	_sectorEnemyIdxV[1].push_back({ 3, 0 });
	_sectorEnemyIdxV[1].push_back({ 5, 1 });

	_sectorEnemyIdxV[2].push_back({ 4, 0 });
	_sectorEnemyIdxV[2].push_back({ 7,0 });

	_sectorEnemyIdxV[3].push_back({ 6, 1 });
	_sectorEnemyIdxV[3].push_back({ 6, 2 });

	_sectorEnemyIdxV[4].push_back({ 7,1 });
	_sectorEnemyIdxV[4].push_back({ 6, 0 });
}
