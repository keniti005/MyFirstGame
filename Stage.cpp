#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),XSIZE(10),ZSIZE(10)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	transform_.scale_ = XMFLOAT3(5.0f, 5.0f, 5.0f);
	transform_.position_.y -= transform_.scale_.y / 2.0f;
	hModel_ = Model::Load("Cube.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < ZSIZE; j++)
		{
			transform_.position_.x = transform_.scale_.x * i;
			transform_.position_.z = transform_.scale_.z * j;
			Model::SetTransform(hModel_, transform_);
			Model::Draw(hModel_);
		}
	}
}

void Stage::Release()
{
	Model::Release();
}
