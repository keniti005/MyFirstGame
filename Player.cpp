#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
#include "Bullet.h"
#include "Engine/SceneManeger.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx_(nullptr)
{
	//pFbx_ = new Fbx;
	//pFbx_->Load("Oden.fbx");
}

Player::~Player()
{
}

void Player::Initialize()
{
	//transform_.scale_.x = 0.7f;
	//transform_.scale_.y = 0.7f;
	//transform_.scale_.z = 0.7f;
	hModel_ = Model::Load("oden.fbx");
	assert(hModel_ >= 0);
	//pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	//pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	//pRChildOden_->SetPostion(2.0f, 1.0f, 0.0f);
	//pLChildOden_->SetPostion(-2.0f, 1.0f, 0.0f);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	transform_.rotate_.y += 0.5f;
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet = Instantiate<Bullet>(pParent_);
		pBullet->SetPostion(transform_.position_);
	}
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
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vCam = { 0,3.0f,-7.0f,0 };
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
	//if (transform_.rotate_.y >= 720.0f)
	//{
	//	KillMe();
	//}
}

void Player::Draw()
{
	//if (pFbx_)
	//{
	//	pFbx_->Draw(transform_);
	//}
	Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
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

void Player::onCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		//KillMe();
		SceneManeger* pSceneManeger = (SceneManeger*)FindObject("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_GAMEOVER);
	}
}
