#pragma once

#include <d3d11.h>
#include<windows.h>
#include<assert.h>

//リンカ
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE
{
	SHADER_3D,//3D用シェーダー
	SHADER_2D,//2D用シェーダー
	SHADER_MAX//シェーダーの最大数
};

namespace Direct3D
{
	extern ID3D11Device* pDevice;		                    //デバイス
	extern ID3D11DeviceContext* pContext;		            //デバイスコンテキスト
	#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
	#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);//シェーダーセット

	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
}