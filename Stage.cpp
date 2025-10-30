#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
	hModel_ = Model::Load("ground.fbx");
	transform_.position_.y = -2.0f;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
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
