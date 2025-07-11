#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"

using namespace DirectX;

struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP;//world*view*projectionの行列
};

struct VERTEX
{
	XMVECTOR pos;
	XMVECTOR uv;
};

class Texture;

class Quad
{
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;//テクスチャ
};