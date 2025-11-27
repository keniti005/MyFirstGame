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
	transform_.scale_ = XMFLOAT3(15.0f, 1.0f, 15.0f);
	transform_.position_.y -= transform_.scale_.y / 2.0f;
	hModel_ = Model::Load("Cube.fbx");
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
