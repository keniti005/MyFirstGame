#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;//world*view*projection行列
		XMMATRIX	matNormal;//法線変換用の行列
	};

	struct VERTEX
	{
		XMVECTOR position;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数

	ID3D11Buffer* pVertexBuffer_;//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
};