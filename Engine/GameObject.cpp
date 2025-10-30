#include "GameObject.h"

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
		return this;//RootJob‚Ì‚±‚Æ
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
		return this;//Ž©•ª‚ª’T‚³‚ê‚Ä‚¢‚½
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;//Œ©‚Â‚©‚Á‚½
			}
		}
		return nullptr;//Œ©‚Â‚©‚ç‚È‚©‚Á‚½
	}
}

GameObject* GameObject::FindObjectByName(const std::string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}
