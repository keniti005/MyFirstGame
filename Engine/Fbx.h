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

struct RayCastData
{
	XMFLOAT3 start;//Rayの始点
	XMFLOAT3 dir;//Rayの方向（正規化してあること）
	bool isHit;//当たったかどうか
	float dist;//始点からの距離
};

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

	std::vector<VERTEX> pVertices_;//頂点データ全部
	std::vector<std::vector<int>> ppIndex_;//マテリアルごとのインデックスデータ[material][index]

	ID3D11Buffer* pVertexBuffer_;//頂点バッファ
	ID3D11Buffer** pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ
	std::vector<MATERIAL> materialList_;
	std::vector<int> indexCount_;

	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)//行列式を解く関数
	{
		return(a.x * b.y * c.z
			+ a.y * b.z * c.x
			+ a.z * b.x * c.y
			- a.z * b.y * c.x
			- a.y * b.x * c.z
			- a.x * b.z * c.y
			);
	}
	bool InterSect(XMFLOAT3 origin, XMFLOAT3 ray, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
	{
		// ---- ベクトルの準備 ----
		// Ray の始点・方向、三角形の頂点を XMVECTOR に変換
		// （DirectXMath で計算するため）
		XMVECTOR vOrigin = XMLoadFloat3(&origin);
		XMVECTOR vRay = XMLoadFloat3(&ray);
		XMVECTOR vV0 = XMLoadFloat3(&v0);
		XMVECTOR vV1 = XMLoadFloat3(&v1);
		XMVECTOR vV2 = XMLoadFloat3(&v2);

		//--------------------------------------
		// 三角形の 2 本の辺ベクトルを作る
		//--------------------------------------
		// edge1 = v1 - v0  （三角形の一辺）
		// edge2 = v2 - v0  （三角形のもう一辺）
		XMVECTOR vEdge1 = vV1 - vV0;
		XMVECTOR vEdge2 = vV2 - vV0;

		//行列式計算のため、XMFLOAT3に戻す
		XMFLOAT3 edge1;
		XMFLOAT3 edge2;
		XMStoreFloat3(&edge1, vEdge1);
		XMStoreFloat3(&edge2, vEdge2);

		//--------------------------------------
		// d = origin - v0
		//--------------------------------------
		// 三角形の基準点 v0 から、Ray の開始点 origin へのベクトル
		// 連立方程式
		//   t*ray = (v0 - origin) + u*edge1 + v*edge2
		// を作るための準備
		XMFLOAT3 d;
		XMStoreFloat3(&d, vOrigin - vV0);

		//--------------------------------------
		// ray を反転（-ray）
		//--------------------------------------
		// 連立方程式を
		//   u*edge1 + v*edge2 + t*(-ray) = d
		// の形にそろえるため、ray に -1 を掛ける
		ray = {
			ray.x * -1.0f,
			ray.y * -1.0f,
			ray.z * -1.0f
		};

		//--------------------------------------
		// 連立方程式の分母（行列式）
		//--------------------------------------
		// denom = det(edge1, edge2, -ray)
		// → 3 本のベクトルが作る行列の行列式
		// → 0 なら、平面と Ray が平行で交点を持たない
		float denom = Det(edge1, edge2, ray);

		// 平行（解なし）の判定
		if (denom <= 0.0f)
		{
			// Ray が三角形の平面と交差しない
			return false;
		}

		//--------------------------------------
		// クラメルの公式で u, v, t を求める
		//--------------------------------------

		// u = det(d, edge2, -ray) / denom
		// → 交点が edge1 方向にどれだけ進んだか（重心座標 u）
		float u = Det(d, edge2, ray) / denom;

		// v = det(edge1, d, -ray) / denom
		// → 交点が edge2 方向にどれだけ進んだか（重心座標 v）
		float v = Det(edge1, d, ray) / denom;

		// t = det(edge1, edge2, d) / denom
		// → Ray の開始点から交点までの距離
		float t = Det(edge1, edge2, d) / denom;

		//--------------------------------------
		// 三角形内部 ＋ Ray の向き 判定
		//--------------------------------------
		// t >= 0  : Ray の前方向に交点がある
		// u >= 0  : v0 → v1 方向に外れていない
		// v >= 0  : v0 → v2 方向に外れていない
		// u + v <= 1 : 三角形の内部に入っている
		if (t >= 0 && u >= 0 && v + v >= 0 && u + v <= 1)
		{
			return true;
		}

		return false;
	}

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(FbxNode* pNode);
	void RayCast(RayCastData& rayData);
};