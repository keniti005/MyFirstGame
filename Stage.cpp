#include "Stage.h"
#include "Engine/Model.h"
#include "Tree.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("ground.fbx");
	//hModel_ = Model::Load("tree.fbx");
	//hModel_ = Model::Load("goalFlag.fbx");
	assert(hModel_ >= 0);
	transform_.position_.y = -2.0f;
	for (int i = 0; i < treeData_.size(); i++)
	{
		for (int j = 0; j < treeData_[i].size(); j++)
		{
			if (treeData_[i][j] == 1)
			{
				tree_ = (Tree*)Instantiate<Tree>(this);
				tree_->SetPostion(1.0f + i * 5.0f, 0.0f, 1.0f + j * 5.0f);
			}
		}
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
	Model::Release();
}
