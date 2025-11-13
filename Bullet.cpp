#include "Bullet.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet")
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Bullet.fbx");

	SphereCollider* col = new SphereCollider(0.4f);
	AddCollider(col);
}

void Bullet::Update()
{
	transform_.position_.z += 0.2f;
	if (transform_.position_.z >= 60.0f)
	{
		KillMe();
	}
}

void Bullet::Draw()
{
	pFbx_->Draw(transform_);
}

void Bullet::Release()
{
}

void Bullet::onCollision(GameObject* pTarget)
{
}
