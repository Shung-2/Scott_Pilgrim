#include "stdafx.h"
#include "PlayerControler.h"

void PlayerControler::Init()
{
	jumpPower = 0;
	gravity = 12.0f;
	dir = false;//false 면 오른쪽 true면 왼쪽
	isJump = false;
	animator = gameObject->GetComponent<Animator>();
	state = IDLE_RIGHT;
	collider = gameObject->GetComponent<BoxCollider>();
	speed = 100;
}

void PlayerControler::Update()
{
	if (CheckGround() == false) {
 		isJump = true;
	}
	if (isDive == true) {
		diveTime++;
		if (diveTime >= 35) {
			collider->enable = true;
			diveTime = 0;
			isDive = false;
		}
	}
	switch (state)
	{
	case IDLE_RIGHT:
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			animator->SetClip(animator->GetClip("run_right"));
			state = RUN_RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			animator->SetClip(animator->GetClip("run_left"));
			state = RUN_LEFT;
			dir = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && isJump == false) {
			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
				isJump = true;
				isDive = true;
				state = JUMP_RIGHT;
				animator->SetClip(animator->GetClip("jump_right"));
				collider->enable = false;
			}
			else {
				isJump = true;
				jumpPower = 8;
				state = JUMP_RIGHT;
				animator->SetClip(animator->GetClip("jump_right"));
			}
		}
		break;
	case IDLE_LEFT:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			animator->SetClip(animator->GetClip("run_left"));
			state = RUN_LEFT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			animator->SetClip(animator->GetClip("run_right"));
			state = RUN_RIGHT;
			dir = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && isJump == false) {
			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
				isJump = true;
				isDive = true;
				state = JUMP_LEFT;
				animator->SetClip(animator->GetClip("jump_left"));
				collider->enable = false;
			}
			else {
				isJump = true;
				jumpPower = 8;
				state = JUMP_LEFT;
				animator->SetClip(animator->GetClip("jump_left"));
			}
		}
		break;
	case RUN_RIGHT:
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
			animator->SetClip(animator->GetClip("idle_right"));
			state = IDLE_RIGHT;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && isJump == false) {
			isJump = true;
			jumpPower = 8;
			state = JUMP_RIGHT;
			animator->SetClip(animator->GetClip("jump_right"));
		}
		break;
	case RUN_LEFT:
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
			animator->SetClip(animator->GetClip("idle_left"));
			state = IDLE_LEFT;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && isJump == false) {
			isJump = true;
			jumpPower = 8;
			state = JUMP_LEFT;
			animator->SetClip(animator->GetClip("jump_left"));
		}
		break;
	case JUMP_RIGHT:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			state = JUMP_LEFT;
			animator->SetClip(animator->GetClip("jump_left"), animator->curClip->currentFrame);
			dir = true;
		}
		break;
	case JUMP_LEFT:
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			state = JUMP_RIGHT;
			animator->SetClip(animator->GetClip("jump_right"), animator->curClip->currentFrame);
			dir = false;
		}
		break;
	case WALL_RIGHT:
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
			isWall = false;
			state = FALL_LEFT;
			animator->SetClip(animator->GetClip("fall_left"));
			dir = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
			isJump = true;
			isWall = false;
			jumpPower = 8;
			wallJumpPower = 5;
			state = JUMP_RIGHT;
			animator->SetClip(animator->GetClip("jump_right"));
		}
		break;
	case WALL_LEFT:
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
			isWall = false;
			state = FALL_RIGHT;
			animator->SetClip(animator->GetClip("fall_right"));
			dir = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
			isJump = true;
			isWall = false;
			jumpPower = 8;
			wallJumpPower = -5;
			state = JUMP_LEFT;
			animator->SetClip(animator->GetClip("jump_left"));
		}
		break;
	default:
		break;
	}
	bool isMoveX;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		isMoveX = transform->MoveX(speed * TIMEMANAGER->getElapsedTime());
		if (isMoveX == false && (state == JUMP_RIGHT || state == FALL_RIGHT)) {
			state = WALL_RIGHT;
			animator->SetClip(animator->GetClip("wall_right"));
			isWall = true;
			jumpPower = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		isMoveX = transform->MoveX(-(speed * TIMEMANAGER->getElapsedTime()));
		if (isMoveX == false && (state == JUMP_LEFT || state == FALL_LEFT)) {
			state = WALL_LEFT;
			animator->SetClip(animator->GetClip("wall_left"));
			isWall = true;
			jumpPower = 0;
		}
	}
	if (isWall == true) {
		if (transform->MoveY(1) == false) {
			if (state == WALL_LEFT) {
				state = IDLE_RIGHT;
				animator->SetClip(animator->GetClip("idle_right"));
			}
			else {
				state = IDLE_LEFT;
				animator->SetClip(animator->GetClip("idle_left"));
			}
			isWall = false;
		}
	}
	if (isJump == true && isWall == false) {
		jumpPower -= gravity * TIMEMANAGER->getElapsedTime();
		if (jumpPower < 0 && jumpPower >= -gravity) {
			if (dir == false) {
				isWall = false;
				state = FALL_RIGHT;
				animator->SetClip(animator->GetClip("fall_right"));
			}
			else {
				isWall = false;
				state = FALL_LEFT;
				animator->SetClip(animator->GetClip("fall_left"));
			}
		}
		if (transform->MoveY(-jumpPower) == false && isDive == false) {
			isJump = false;
			jumpPower = 0;
			if (state == FALL_RIGHT) {
				animator->SetClip(animator->GetClip("ground_right"));
				state = IDLE_RIGHT;
			}
			else if (state == FALL_LEFT) {
				animator->SetClip(animator->GetClip("ground_left"));
				state = IDLE_LEFT;
			}
		}
		transform->MoveX(-wallJumpPower);
		if (wallJumpPower > 0) {
			wallJumpPower -= gravity * TIMEMANAGER->getElapsedTime();
			if (wallJumpPower < 0)
				wallJumpPower = 0;
		}
		if (wallJumpPower < 0) {
			wallJumpPower += gravity * TIMEMANAGER->getElapsedTime();
			if (wallJumpPower > 0)
				wallJumpPower = 0;
		}

	}
	sprintf_s(debug[1], "%d", isJump);
	DebugState();
}

void PlayerControler::Render()
{
	if(!KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(BackBuffer, groundRc);
}

bool PlayerControler::CheckGround()
{
	RECT intersectRc;
	RECT* targetRc;
	bool result = false;
	int colNum = COLLIDERMANAGER->colliderList.size();
	if (collider == nullptr)
		return result;
	groundRc = RectMakeCenter(transform->GetX(), collider->rc.bottom + 1, collider->width, 2);
	for (int i = 0; i < colNum; i++) {
		if (collider == COLLIDERMANAGER->colliderList[i]) continue;
		if (COLLIDERMANAGER->colliderList[i]->isTrigger == true) continue;
		targetRc = &COLLIDERMANAGER->colliderList[i]->rc;
		if (IntersectRect(&intersectRc, &groundRc, targetRc)) {
			int w = intersectRc.right - intersectRc.left;
			int h = intersectRc.bottom - intersectRc.top;
			if (intersectRc.bottom < GetCenterY(*targetRc) && w > h) {
				result = true;
				return result;
			}
		}
	}
	return result;
}

void PlayerControler::DebugState()
{
	switch (state)
	{
	case IDLE_RIGHT:
		sprintf_s(debug[0], "IDLE_RIGHT");
		break;
	case IDLE_LEFT:
		sprintf_s(debug[0], "IDLE_LEFT");
		break;
	case RUN_RIGHT:
		sprintf_s(debug[0], "RUN_RIGHT");
		break;
	case RUN_LEFT:
		sprintf_s(debug[0], "RUN_LEFT");
		break;
	case JUMP_RIGHT:
		sprintf_s(debug[0], "JUMP_RIGHT");
		break;
	case JUMP_LEFT:
		sprintf_s(debug[0], "JUMP_LEFT");
		break;
	case WALL_RIGHT:
		sprintf_s(debug[0], "WALL_RIGHT");
		break;
	case WALL_LEFT:
		sprintf_s(debug[0], "WALL_LEFT");
		break;
	default:
		break;
	}
}


