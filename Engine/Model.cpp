#include "Model.h"
#include "Direct3D.h"

namespace Model
{
    std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
    ModelData* pModelData = new ModelData;
    pModelData->filename_ = fileName;
    pModelData->pfbx_ = nullptr;
    for (auto& itr : modelList)
    {
        if (itr->filename_ == fileName)
        {
            pModelData->pfbx_ = itr->pfbx_;
            break;
        }
    }

    if (pModelData->pfbx_ == nullptr)
    {
        pModelData->pfbx_ = new Fbx;
        pModelData->pfbx_->Load(fileName.c_str());
    }
    modelList.push_back(pModelData);
    return((int)(modelList.size() - 1));
}

void Model::SetTransform(int hModel, Transform transform)
{
    modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
    modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
    bool isReferd = false;//参照されているか
    for (int i = 0;i < modelList.size(); i++)
    {
        for (int j = i + 1;j < modelList.size();j++)
        {
            if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
            {
                isReferd = true;
                break;
            }
        }
        if (isReferd == false)
        {
            SAFE_DELETE(modelList[i]->pfbx_);
        }
        SAFE_DELETE(modelList[i]);
    }
    modelList.clear();//配列を空にする
}

void Model::RayCast(int hModel, RayCastData& rayData)
{
    //その時点での対象モデルのトランスフォームをカリキュレーション
    modelList[hModel]->transform_.Calculation();

    //ワールド行列取得
    XMMATRIX worldMatrix = modelList[hModel]->transform_.GetWorldMatrix();

    //ワールド行列の逆行列
    XMMATRIX wInv = XMMatrixInverse(nullptr,worldMatrix);

    //レイの通過地点を求める
    XMVECTOR vDirVec{ rayData.start.x + rayData.dir.x,rayData.start.y + rayData.dir.y,rayData.start.z + rayData.dir.z,0.0f };

    //rayData.startをモデル空間に変換
    XMVECTOR vstart = XMLoadFloat3(&rayData.start);
    //https://learn.microsoft.com/ja-jp/windows/win32/api/directxmath/
    // //ここから、3次元ベクトルの変換関数を探す w=1のときの変換
    vstart = XMVector3Transform(vstart,wInv);
    XMStoreFloat3(&rayData.start, vstart);//変換結果をrayData.startに格納

    //(始点から方向ベクトルをちょい伸ばした先)通過点にかける(モデル空間に変換)
    vDirVec = XMVector3Transform(vDirVec,wInv);

    //rayData.dirをvstartからvDirVecに向かうベクトルにする
    XMVECTOR dirAtLocal = XMVectorSubtract(vDirVec , vstart);
    dirAtLocal = XMVector3Normalize(dirAtLocal);
    XMStoreFloat3(&rayData.dir, dirAtLocal);//変換結果をrayData.dirに格納

    //指定したモデル番号のFBXにレイキャスト
    modelList[hModel]->pfbx_->RayCast(rayData);
}
