#include "stdafx.h"
#include "Projectile.h"

void Projectile::Init(string targetTag, string hitEffectName, int damage, float activeLimit)
{
	_targetTag = TAGMANAGER->GetTag(targetTag);
	_hitEffectName = hitEffectName;
	_damage = damage;
	_activeLimit = activeLimit;
	_activeTime = 0;
	_isNeedEffectDir = false;
}

void Projectile::Update()
{
	_activeTime += TIMEMANAGER->getElapsedTime();
	if (_activeTime >= _activeLimit) {
		gameObject->SetActive(false);
		_activeTime = 0;
	}
}

void Projectile::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == _targetTag) {
		this->gameObject->SetActive(false);
		if (_hitEffectName.compare("none") != 0) {
			if (_isNeedEffectDir == true) {
				string effectName = _hitEffectName;
				if (_dir == false)
					effectName.append("_right");
				else
					effectName.append("_left");
				EffectManager::getInstance()->EmissionEffect(effectName, transform->GetX(), transform->GetY());
			}
			else {
				EffectManager::getInstance()->EmissionEffect(_hitEffectName, transform->GetX(), transform->GetY());
			}
		}
		gameObject->GetComponent<ObjectInfo>()->Damage(_damage);
	}
}

void Projectile::Fire(int x, int y, bool dir)
{
	_dir = dir;
	_activeTime = 0;
	transform->SetPosition(x, y);
	gameObject->GetComponent<BoxCollider>()->prevCol.clear();
	if (dir == false) {
		gameObject->GetComponent<Animator>()->SetClip(
			gameObject->GetComponent<Animator>()->GetClip("right")
		);
	}
	else {
		gameObject->GetComponent<Animator>()->SetClip(
			gameObject->GetComponent<Animator>()->GetClip("left")
		);
	}
	gameObject->SetActive(true);
}
