#pragma once

#include <list>
#include <string>
#include "Transform.h"

class SphereCollider;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	virtual void onCollision(GameObject* pTarget) {};
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void SetPostion(XMFLOAT3 position);
	void SetPostion(float x, float y, float z);
	void KillMe();

	GameObject* GetRootJob();
	GameObject* FindChildObject(const std::string& name);
	GameObject* FindObject(const std::string& name);

	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
	std::string GetObjectName();

	template<class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}
protected:
	std::list<GameObject*> childList_;
	Transform	transform_;
	GameObject* pParent_;
	std::string	objectName_;
	SphereCollider* pCollider_;
private:
	bool isDead_;
};