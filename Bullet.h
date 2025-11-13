#pragma once
#include "Engine/GameObject.h"

class Fbx;

class Bullet :
	public GameObject
{
public:
	Bullet(GameObject* parent);
	~Bullet();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void onCollision(GameObject* pTarget)override;
private:
	Fbx* pFbx_;
};