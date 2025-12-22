#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

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
	XMFLOAT3 mousePosFront;
	XMStoreFloat3(&mousePosFront, Input::GetMousePosition());
	mousePosFront.z = 0.0f;

	XMFLOAT3 mousePosBack;
	XMStoreFloat3(&mousePosBack, Input::GetMousePosition());
	mousePosBack.z = 1.0f;


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

	Transform t;
	t.position_.x = 5;
	t.position_.y = 0;
	t.position_.z = 5;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	RayCastData data{
		{ 0.0f, 0.0f, 5.0f },
		{ 0.0f,-1.0f, 0.0f },
		false,
		0.0f
	};

	Model::RayCast(hModel_, data);

	if (data.isHit)
	{
		int a = 0;
		a++;
	}

	//Transform t;
	//t.position_.x = 5;
	//t.position_.y = 0;
	//t.position_.z = 5;
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
	//RayCastData data{
	//	{ 0.0f, 0.0f, 5.0f, 0.0f },
	//	{ 0.0f,-1.0f, 0.0f, 0.0f },
	//	false,
	//	0.0f
	//};
	//
	//Model::RayCast(hModel_, data);
	//
	//if (data.isHit)
	//{
	//	int a = 0;
	//	a++;
	//}

	//Model::SetTransform(hModel_, transform_);
}

void Stage::Release()
{
	Model::Release();
}
