#include "Dice.h"
#include <DirectXMath.h>
#include "Camera.h"

using namespace  DirectX;

Dice::Dice()
	:Quad()
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	HRESULT hr;

	VERTEX vertices[] =
	{
		//{{position}, {uv}}
		//前面
		{{-1.0f, 1.0f,-1.0f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 0.0f, -1.0f, 0.0f}},//左上
		{{ 1.0f, 1.0f,-1.0f, 0.0f},{ 1.0f, 0.0f},{ 0.0f, 0.0f, -1.0f, 0.0f}},//右上
		{{ 1.0f,-1.0f,-1.0f, 0.0f},{ 1.0f, 1.0f},{ 0.0f, 0.0f, -1.0f, 0.0f}},//右下
		{{-1.0f,-1.0f,-1.0f, 0.0f},{ 0.0f, 1.0f},{ 0.0f, 0.0f, -1.0f, 0.0f}},//左下
		//後面
		{{-1.0f, 1.0f,+1.0f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 0.0f, 1.0f, 0.0f}},//左上
		{{ 1.0f, 1.0f,+1.0f, 0.0f},{ 1.0f, 0.0f},{ 0.0f, 0.0f, 1.0f, 0.0f}},//右上
		{{ 1.0f,-1.0f,+1.0f, 0.0f},{ 1.0f, 1.0f},{ 0.0f, 0.0f, 1.0f, 0.0f}},//右下
		{{-1.0f,-1.0f,+1.0f, 0.0f},{ 0.0f, 1.0f},{ 0.0f, 0.0f, 1.0f, 0.0f}},//左下
		//右側
		{{ 1.0f, 1.0f,-1.0f, 0.0f},{ 0.0f, 0.0f},{ 1.0f, 0.0f, 0.0f, 0.0f}},//左上
		{{ 1.0f, 1.0f,+1.0f, 0.0f},{ 1.0f, 0.0f},{ 1.0f, 0.0f, 0.0f, 0.0f}},//右上
		{{ 1.0f,-1.0f, 1.0f, 0.0f},{ 1.0f, 1.0f},{ 1.0f, 0.0f, 0.0f, 0.0f}},//右下
		{{ 1.0f,-1.0f,-1.0f, 0.0f},{ 0.0f, 1.0f},{ 1.0f, 0.0f, 0.0f, 0.0f}},//左下
		//左側
		{{-1.0f, 1.0f,-1.0f, 0.0f},{ 0.0f, 0.0f},{-1.0f, 0.0f, 0.0f, 0.0f}},//左上
		{{-1.0f, 1.0f,+1.0f, 0.0f},{ 1.0f, 0.0f},{-1.0f, 0.0f, 0.0f, 0.0f}},//右上
		{{-1.0f,-1.0f, 1.0f, 0.0f},{ 1.0f, 1.0f},{-1.0f, 0.0f, 0.0f, 0.0f}},//右下
		{{-1.0f,-1.0f,-1.0f, 0.0f},{ 0.0f, 1.0f},{-1.0f, 0.0f, 0.0f, 0.0f}},//左下
		//上側
		{{-1.0f, 1.0f, 1.0f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, 1.0f, 0.0f, 0.0f}},//左上
		{{ 1.0f, 1.0f, 1.0f, 0.0f},{ 1.0f, 0.0f},{ 0.0f, 1.0f, 0.0f, 0.0f}},//右上
		{{ 1.0f, 1.0f,-1.0f, 0.0f},{ 1.0f, 1.0f},{ 0.0f, 1.0f, 0.0f, 0.0f}},//右下
		{{-1.0f, 1.0f,-1.0f, 0.0f},{ 0.0f, 1.0f},{ 0.0f, 1.0f, 0.0f, 0.0f}},//左下
		//下側
		{{-1.0f,-1.0f, 1.0f, 0.0f},{ 0.0f, 0.0f},{ 0.0f, -1.0f, 0.0f, 0.0f}},//左上
		{{ 1.0f,-1.0f, 1.0f, 0.0f},{ 1.0f, 0.0f},{ 0.0f, -1.0f, 0.0f, 0.0f}},//右上
		{{ 1.0f,-1.0f,-1.0f, 0.0f},{ 1.0f, 1.0f},{ 0.0f, -1.0f, 0.0f, 0.0f}},//右下
		{{-1.0f,-1.0f,-1.0f, 0.0f},{ 0.0f, 1.0f},{ 0.0f, -1.0f, 0.0f, 0.0f}},//左下

	};
	int index[] =
	{
		0,1,2,0,3,2,//前面
		4,5,6,4,6,7,//後面
		8,9,10,8,10,11,//右側
		12,13,14,12,14,15,//左側
		16,17,18,16,18,19,//上側
		20,21,22,20,22,23//下側
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	////インデックス情報
	//int index[] = { 0,2,3, 0,1,2 };//CW

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	pTexture_ = new Texture();
	pTexture_->Load("dice.png");

	return S_OK;

}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	Direct3D::SetShader(SHADER_3D);
	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(XMMatrixInverse(nullptr, worldMatrix));
	cb.matWorld = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
	

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->DrawIndexed(36, 0, 0);

}

void Dice::Release()
{
}
