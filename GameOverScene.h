#pragma once
#include "Engine/GameObject.h"

class Sprite;

class GameOverScene :
	public GameObject
{
public:
    GameOverScene(GameObject* parent);
    ~GameOverScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    Sprite* pSprite;
};