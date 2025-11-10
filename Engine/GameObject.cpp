#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), isDead_(false)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr : childList_)
	{
		itr->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	transform_.Calculation();
	Update();

	RoundRobin(GetRootJob());
	for (auto itr : childList_)
	{
		itr->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_)
	{
		itr->ReleaseSub();
	}
}

void GameObject::SetPostion(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPostion(float x, float y, float z)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	transform_.position_.z = z;
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;//RootJobのこと
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const std::string& name)
{
	if (this->objectName_ == name)
	{
		return this;//自分が探されていた
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;//見つかった
			}
		}
		return nullptr;//見つからなかった
	}
}

GameObject* GameObject::FindObjectByName(const std::string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;

}

void GameObject::Collision(GameObject* pTarget)
{
	float thisR = this->pCollider_->GetRadius();
	float tgtR = pTarget->pCollider_->GetRadius();
	float thre = (thisR - tgtR) * (thisR - tgtR);
	
	XMFLOAT3 thisP = this->transform_.position_;
	XMFLOAT3 tgtP = pTarget->transform_.position_;
	float dist = (thisP.x - tgtP.x) * (thisP.x - tgtP.x) +
				 (thisP.y - tgtP.y) * (thisP.y - tgtP.y) +
				 (thisP.z - tgtP.z) * (thisP.z - tgtP.z);
	if (dist <= thre)
	{
		MessageBoxA(0, "ぶつかった", "Collider", MB_OK);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//自分にコライダーがなかったらreturn
	if (pCollider_ == nullptr)
	{
		return;
	}
	//自分とターゲット自体のコライダーの当たり判定
	if (pTarget->pCollider_ != nullptr)
	{
		Collision(pTarget);
	}
	for (auto itr : pTarget->childList_)
	{
		RoundRobin(itr);
	}
}
