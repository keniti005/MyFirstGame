#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

namespace
{
	const int XSIZE = 10;
	const int ZSIZE = 10;
	const int MODEL_NUM = 5;
}

enum BLOCK_TYPE
{
	DEFAULT,
	BRICK,
	GRASS,
	SAND,
	WATER
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
	BOOL localProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	BOOL menuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//操作パネル用のプロシージャ
	void SetBlock(BLOCK_TYPE type, int x, int z) { GetT(x, z).type = type; }
	void SetBlockHeight(int x, int z, int height) { GetT(x, z).height = height; }
	sData& GetT(int x, int z) { return sTable[z][x]; }
private:
	int hModel_;
	sData sTable[ZSIZE][XSIZE];
	int hModel[MODEL_NUM];
	int mode_;//0:上げる 1:下げる 2:種類変更
	int select_;//ボックスの種類
};