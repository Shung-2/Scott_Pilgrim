#pragma once
#define PI 3.14159f
#define PI2 PI * 2
#include "GameObject.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "PlayerControler.h"
#include "ObjectInfo.h"
#include "UIRenderer.h"
#include "Cam.h"
#include "Camera.h"
#include "UIBase.h"
#include "Text.h"
#include "Box.h"
#include "Zone.h"
#include "Item.h"
#include "ImageObject.h"
#include "Shadow.h"
#include "Character.h"
#include "Ground.h"
#include "ZOrder.h"
#include "ItemObject.h"
#include "DebugText.h"
#include "Wall.h"
#include "WallObj.h"
#include "Player.h"
#include "MapManager.h"
#include "Matthew.h"
#include <typeinfo>

// 210625~ 시영 Enemy 작업 관련 include
#include "Enemy.h"
#include "EnemyAI.h"
#include "EnemyInfo.h"
#include "EnemyState.h"
#include "Jesse.h"
#include "Lee.h"
#include "Luke.h"
#include "Mike.h"
#include "Richard.h"

//광철 애너미
#include "Doberman.h"
#include "Malcolm.h"
#include "William.h"

typedef RECT ELLIPSE;
typedef struct tagPOINTF {
	float x;
	float y;
}POINTF;

namespace HDY_UTIL
{
	float GetDistance(float x1, float y1, float x2, float y2);
	template <typename T>
	T GetDistance(T x1, T x2);

	float GetAngle(float x1, float y1, float x2, float y2);

	int GetCenterX(RECT rc);
	int GetCenterY(RECT rc);
	POINT GetCenter(RECT rc);
	POINTF GetCenterF(RECT rc);
	int GetWidth(RECT rc);
	int GetHeight(RECT rc);
	int GetRadius(ELLIPSE rc);
	template <typename T>
	T GetCenter(T a, T b);
	POINTF GetCollisionPoint(RECT rc1, RECT rc2);
	POINTF MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit = 0);
	POINTF MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit = 0);
}