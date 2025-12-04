#include "Area.h"
#include <string>
#include "Engine/Model.h"

Area::Area(GameObject* parent)
	:GameObject(parent,"Area")
{
}

Area::~Area()
{
}

void Area::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	transform_.position_.y = 0.5f;
	//Model_ = Model::Load("lakeArea.fbx");
}

void Area::Update()
{
}

void Area::Draw()
{
	//Model::SetTransform(Model_,transform_);
	//Model::Draw(Model_);
}

void Area::Release()
{
	//Model::Release();
}
