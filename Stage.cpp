#include "Stage.h"
#include "Engine/Model.h"
#include "Tree.h"
#include "Area.h"
#include "Engine/CsvReader.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	hModel_ = Model::Load("ground.fbx");
	//hModel_ = Model::Load("goalFlag.fbx");
	assert(hModel_ >= 0);
	transform_.position_.y = -2.0f;
	Instantiate<Tree>(this);
	Instantiate<Area>(this);
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
