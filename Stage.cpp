#include "Stage.h"
#include "Engine/Model.h"

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
