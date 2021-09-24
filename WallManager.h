#pragma once
class Wall;
class WallManager : public singletonBase<WallManager>
{
private:
	vector<Wall*> _wallV;
public:
	void Init();
	void Release();

	void AddWall(Wall* newWall) { _wallV.push_back(newWall); }
	void EraseWall(Wall* targetWall);

	bool CheckCross(float startX, float startY, float endX, float endY);
	bool CheckCross(float startX, float startY, float endX, float endY, int idx);
};

