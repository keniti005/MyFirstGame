#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name)
{
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
	Update();
	for (auto itr : childList_)
	{
		itr->UpdateSub();
	}
}
