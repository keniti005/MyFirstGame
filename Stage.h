#pragma once
#include "Engine/GameObject.h"

enum BLOCK_TYPE
{
	DEFAULT,
	WATER,
	SAND
};

struct sData
{
	BLOCK_TYPE type;
	int height;
};

class Stage :
	public GameObject
{
public:
	Stage(GameObject* parent);
	~Stage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hModel_;
	const int XSIZE;
	const int ZSIZE;
};