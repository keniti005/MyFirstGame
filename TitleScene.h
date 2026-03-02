#pragma once
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"

class TitleScene :
    public GameObject
{
public:
    TitleScene(GameObject* parent);
    ~TitleScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    int hModel_;
    Sprite* pSprite_;
};

