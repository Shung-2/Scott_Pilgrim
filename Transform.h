#pragma once
#include <vector>

using namespace std;

class GameObject;

class Transform
{
	typedef struct tagPOSITION {
		float x;
		float y;
	}POSITION;
	typedef struct tagScale {
		int width;
		int height;
	}SCALE;

public:
	Transform();
	~Transform();
	POSITION position;
	SCALE size;
	vector<Transform*> child;
	Transform* parent;
	GameObject* gameObject;
	int siblingIdx;
	bool Move(float x, float y);
	bool MoveX(float x);
	bool MoveY(float y);
	bool CheckCollision(float tempX, float tempY);
	bool CheckWallCross(float deltaX, float deltaY);
	int GetChildCount() { return child.size(); }
	Transform* GetChild(int i);
	void AddChild(GameObject* gameObject);
	void AddChild(Transform* transform);
	void DetachChild(int idx);
	void DetachParent();

	void SetX(float x) { position.x = x; }
	void SetY(float y) { position.y = y; }
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	float GetX() { return position.x; }
	float GetY() { return position.y; }

	void SetWidth(int width) { size.width = width; }
	void SetHeight(int height) { size.height = height; }
	void SetSize(int width, int height) { size.width = width, size.height = height; }
	int GetWidth() { return size.width; }
	int GetHeight() { return size.height; }
};

