#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"
#include <vector>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
private:
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;//world*view*projection行列
		XMMATRIX	matNormal;//法線変換用の行列
		XMFLOAT4	diffuse;
		BOOL		materiaFlag;//マテリアルがあるかないか
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_; //マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;//頂点バッファ
	ID3D11Buffer** pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ
	std::vector<MATERIAL> materialList_;
	std::vector<int> indexCount_;
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(FbxNode* pNode);
};