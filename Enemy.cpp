#include "Enemy.h"
#include "Engine/SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),pFbx_(nullptr)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("oden.fbx");
	transform_.position_ = { 0.0f,0.0f,50.0f };

	SphereCollider* col = new SphereCollider(0.8f);
	AddCollider(col);
}

void Enemy::Update()
{
	transform_.rotate_.y += 1.0f;
}

void Enemy::Draw()
{
	pFbx_->Draw(transform_);
}

void Enemy::Release()
{
}

void Enemy::onCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		KillMe();
	}
}
