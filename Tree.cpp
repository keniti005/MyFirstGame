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
	transform_.scale_.x = 2.0f;
	transform_.scale_.y = 2.0f;
	transform_.scale_.z = 2.0f;
	hModel_ = Model::Load("tree.fbx");
	assert(hModel_ >= 0);
}

void Tree::Update()
{
}

void Tree::Draw()
{
	CsvReader csv;
	csv.Load("assets\\Stage00.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			if (csv.GetValue(i, j) == 1)
			{
				transform_.position_.x =  ((transform_.scale_.x + 3.0f) * i);
				transform_.position_.z = -((transform_.scale_.z + 3.0f) * j);
				Model::SetTransform(hModel_, transform_);
				Model::Draw(hModel_);
			}
		}
	}

}

void Tree::Release()
{
	Model::Release();
}
