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
    bool isReferd = false;//QÆ‚³‚ê‚Ä‚¢‚é‚©
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
    modelList.clear();//”z—ñ‚ğ‹ó‚É‚·‚é
}
