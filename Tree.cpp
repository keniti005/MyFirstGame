#include "Tree.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Tree::Tree(GameObject* parent)
	:GameObject(parent,"Tree")
{
}

Tree::~Tree()
{
}

void Tree::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	hModel_ = Model::Load("tree.fbx");
	assert(hModel_ >= 0);
	//CsvReader csvReader;
	//csvReader.Load("Stage00.csv");
	
}

void Tree::Update()
{
}

void Tree::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tree::Release()
{
	Model::Release();
}
