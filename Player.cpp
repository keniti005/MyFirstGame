#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	//hModel_ = Model::Load("oden.fbx");
	//hModel_ = Model::Load("ironClub.fbx");
	//hModel_ = Model::Load("woodenClub.fbx");
	//hModel_ = Model::Load("smallClub.fbx");
	hModel_ = Model::Load("bollPlayer.fbx");
	assert(hModel_ >= 0);
	//pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	//pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	//pRChildOden_->SetPostion(2.0f, 1.0f, 0.0f);
	//pLChildOden_->SetPostion(-2.0f, 1.0f, 0.0f);
}

void Player::Update()
{
	//transform_.rotate_.y += 0.5f;
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.2f;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.2f;
	}
	if (Input::IsKey(DIK_W))
	{
		transform_.position_.z += 0.2f;
	}
	if (Input::IsKey(DIK_S))
	{
		transform_.position_.z -= 0.2f;
	}
	//if (transform_.rotate_.y >= 720.0f)
	//{
	//	KillMe();
	//}

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vCam = { 0,2.0f,-5.0f,0 };
	XMVECTOR camPos;
	camPos = vPos + vCam;
	Camera::SetPosition(camPos);

	XMVECTOR CamTarget = XMLoadFloat3(&transform_.position_);
	Camera::SetTarget(CamTarget);

	if (Input::IsKey(DIK_UP))
	{
		transform_.position_.y += 0.2f;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.position_.y -= 0.2f;
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
