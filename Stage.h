#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Tree;

class Stage :
    public GameObject
{
public:
    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    int GetModelHandle(){ return hModel_; }
private:
    int hModel_;
    Tree* tree_;
};

