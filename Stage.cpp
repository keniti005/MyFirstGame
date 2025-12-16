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
	transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
	//transform_.position_.y -= transform_.scale_.y / 2.0f;
	hModel_ = Model::Load("Cube.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
	RayCastData data;
	XMStoreFloat3(&data.start, XMVectorSet(0.0f,3.0f,0.0f,0.0f));
	XMStoreFloat3(&data.dir, XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f));
	Transform t;
	t.position_.x = transform_.position_.x;
	t.position_.y = transform_.position_.y;
	t.position_.z = transform_.position_.z;
	Model::SetTransform(hModel_, transform_);

	Model::RayCast(hModel_, data);

	if (data.isHit)
	{
		int a = 0;
		a++;
	}
}

void Stage::Draw()
{
	//for (int i = 0; i < XSIZE; i++)
	//{
	//	for (int j = 0; j < ZSIZE; j++)
	//	{
	//		transform_.position_.x = transform_.scale_.x * i;
	//		transform_.position_.z = transform_.scale_.z * j;
	//		Model::SetTransform(hModel_, transform_);
	//		Model::Draw(hModel_);
	//	}
	//}
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
	Model::Release();
}
