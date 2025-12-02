#pragma once

#include <list>
#include <string>
#include "Transform.h"

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
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void SetPostion(XMFLOAT3 position);
	void SetPostion(float x, float y, float z);
	XMFLOAT3 GetPosition(XMFLOAT3 position) { return transform_.position_; }
	void KillMe();

	GameObject* GetRootJob();
	GameObject* FindChildObject(const std::string& name);
	GameObject* FindObjectByName(const std::string& name);

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
private:
	bool isDead_;
};