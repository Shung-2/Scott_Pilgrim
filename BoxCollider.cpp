#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	COLLIDERMANAGER->colliderList.push_back(this);
	width = 100;
	height = 100;
	isTrigger = false;
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Update()
{
	rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
	if (isTrigger == false) return;
	int colNum = COLLIDERMANAGER->colliderList.size();
	for (int i = 0; i < colNum; i++) {
		if (CheckCollision(GetCenterX(rc), GetCenterY(rc), i)) {
			vCol.push_back(i);
		}
	}
	for (int i = 0; i < vCol.size(); i++) {
		bool isExist = false;
		for (int j = 0; j < prevCol.size(); j++) {
			 if(vCol[i] == prevCol[j]) {
				if (gameObject->isActive == true)
					gameObject->OnTriggerStay(COLLIDERMANAGER->colliderList[prevCol[j]]->gameObject);
				isExist = true;
				break;
			}
		}
		if (isExist == false) {
			if(gameObject->isActive == true)
				gameObject->OnTriggerEnter(COLLIDERMANAGER->colliderList[vCol[i]]->gameObject);
		}
	}

	for (int i = 0; i < prevCol.size(); i++) {
		bool isExist = false;
		for (int j = 0; j < vCol.size(); j++) {
			if (vCol[j] == prevCol[i]) {
				isExist = true;
				break;
			}
		}
		if (isExist == false) {
			if (gameObject->isActive == true)
				gameObject->OnTriggerExit(COLLIDERMANAGER->colliderList[prevCol[i]]->gameObject);
		}
	}

	prevCol.clear();
	prevCol.assign(vCol.begin(), vCol.end());
	vCol.clear();
}
bool BoxCollider::CheckCollision(float tempX, float tempY) {
	if (enable == false) {
		return false;
	}
	int colNum = COLLIDERMANAGER->colliderList.size();
	int deltaX = tempX - transform->GetX();
	int deltaY = tempY - transform->GetY();
	int marginX = 0, marginY = 0;
	for (int i = 0; i < colNum; i++) {
		if (CheckCollision(tempX, tempY, i)) {
			if (COLLIDERMANAGER->colliderList[i]->isTrigger == false && this->isTrigger == false) {
				int w = intersectRc.right - intersectRc.left;
				int h = intersectRc.bottom - intersectRc.top;
				if (w <= h) {
					deltaX >= 0 ? marginX = deltaX - w : marginX = deltaX + w;
				}
				else {
					deltaY >= 0 ? marginY = deltaY - h : marginY = deltaY + h;
				}
				string targetName = COLLIDERMANAGER->colliderList[i]->gameObject->name;
				gameObject->OnCollision(COLLIDERMANAGER->colliderList[i]->gameObject);
				if (weight > COLLIDERMANAGER->colliderList[i]->weight) {
					bool isLack = false;
					for (int j = 0; j < colNum; j++) {
						if (COLLIDERMANAGER->colliderList[j]->isTrigger == false  &&
							COLLIDERMANAGER->colliderList[j] != COLLIDERMANAGER->colliderList[i] &&
							CheckCollision(COLLIDERMANAGER->colliderList[i]->rc, j)) {
							string name = COLLIDERMANAGER->colliderList[j]->gameObject->name;
							int bottom = COLLIDERMANAGER->colliderList[i]->rc.bottom;
							int top = COLLIDERMANAGER->colliderList[j]->rc.top;
   							isLack = true;
							break;
						}
					}
					if (isLack == true) {
						COLLIDERMANAGER->colliderList[i]->isTrigger = true;
					}
					else {
						COLLIDERMANAGER->colliderList[i]->transform->Move(deltaX - marginX, deltaY - marginY);
					}
					return false;
				}
				else {
					bool isLack = false;
					for (int j = 0; j < colNum; j++) {
						if (COLLIDERMANAGER->colliderList[j]->isTrigger == false &&
							COLLIDERMANAGER->colliderList[j] != COLLIDERMANAGER->colliderList[i] && 
							CheckCollision(transform->GetX() + marginX, transform->GetY() + marginY, j)) {
							isLack = true;
							string name = COLLIDERMANAGER->colliderList[j]->gameObject->name;
  							break;
						}
					}
					if (isLack == true) {
						this->isTrigger = true;
					}
					else {
						transform->Move(marginX, marginY);
					}
					return true;
				}
			}
		}
	}
	return false;
}
bool BoxCollider::CheckCollision(float tempX, float tempY, int colIdx)
{
	RECT tempRc = RectMakeCenter(tempX, tempY, width, height);
	RECT* targetRc;
	if (&(this->rc) == &(COLLIDERMANAGER->colliderList[colIdx]->rc)) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->gameObject->isActive == false) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->enable == false) return false;
	targetRc = &COLLIDERMANAGER->colliderList[colIdx]->rc;
	if (IntersectRect(&intersectRc, &tempRc, targetRc)) {
		int w = intersectRc.right - intersectRc.left;
		int h = intersectRc.bottom - intersectRc.top;
		if (h >= w) {
			if (intersectRc.right <= GetCenterX(*targetRc)) {
			}
			else {
			}
		}
		else {
		}
		return true;
	}
	return false;
}
bool BoxCollider::CheckCollision(RECT rc, int colIdx)
{
	RECT* targetRc;
	if (&(this->rc) == &(COLLIDERMANAGER->colliderList[colIdx]->rc)) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->gameObject->isActive == false) return false;
	if (COLLIDERMANAGER->colliderList[colIdx]->enable == false) return false;
	targetRc = &COLLIDERMANAGER->colliderList[colIdx]->rc;
	if (IntersectRect(&intersectRc, &rc, targetRc)) {
		int w = intersectRc.right - intersectRc.left;
		int h = intersectRc.bottom - intersectRc.top;
		if (h >= w) {
			if (intersectRc.right <= GetCenterX(*targetRc)) {
			}
			else {
			}
		}
		else {
		}
		return true;
	}
	return false;
}
void BoxCollider::SetWidth(int width)
{
	this->width = width;
	rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
}
void BoxCollider::SetHeight(int height)
{
	this->height = height;
	rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
}
void BoxCollider::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
}
void BoxCollider::Render()
{
	HPEN hPen, oPen;
	HBRUSH hBrush, oBrush;
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		return;
	}
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oBrush = (HBRUSH)SelectObject(BackBuffer, hBrush);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	oPen = (HPEN)SelectObject(BackBuffer, hPen);
	Rectangle(BackBuffer, rc);
	SelectObject(BackBuffer, oPen);
	SelectObject(BackBuffer, oBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void BoxCollider::OnDisable()
{
	COLLIDERMANAGER->EraseCollider(this);
}

void BoxCollider::OnEnable()
{
	COLLIDERMANAGER->AddCollider(this);
}
