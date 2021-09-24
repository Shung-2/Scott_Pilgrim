#pragma once
class Ground;
class GroundManager : public singletonBase<GroundManager>
{
private:
	vector<Ground*> _groundV;
public:
	GroundManager() {};
	~GroundManager() {};
	HRESULT Init();
	void Release();
	void AddGround(Ground* newGround);
	void EraseGround(Ground* targetGround);
	int CheckGround(float x, float y, float z, int width, int height);
	int CheckGround(RECT rc, float z);
	int CheckGround(float x, float y, float z, int width, int height, int idx);
	int CheckGround(RECT rc, float z, int idx);
	RECT GetGroundRect(int idx);
};

