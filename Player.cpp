#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;
	//hModel_ = Model::Load("oden.fbx");
	//hModel_ = Model::Load("golfClub.fbx");
	hModel_ = Model::Load("bollPlayer.fbx");
	assert(hModel_ >= 0);
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pRChildOden_->SetPostion(2.0f, 1.0f, 0.0f);
	pLChildOden_->SetPostion(-2.0f, 1.0f, 0.0f);
}

void Player::Update()
{

	transform_.rotate_.y += 0.5f;
	if (transform_.rotate_.y >= 720.0f)
	{
		KillMe();
	}
}

void Player::Draw()
{
	//if (pFbx_)
	//{
	//	pFbx_->Draw(transform_);
	//}

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
	//if (pFbx_)
	//{
	//	pFbx_->Release();
	//	delete pFbx_;
	//	pFbx_ = nullptr;
	//}
	Model::Release();
}
