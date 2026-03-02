#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"
#include "Engine/Model.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
	pSprite_ = new Sprite("assets\\Title.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	//スペースキー押したら
	//SceneManeger::ChangeScene(SCENE_ID_PLAY);を呼び出す
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Transform t;
	t.scale_ = { 0.5f,0.5f,1.0f };
	t.Calculation();
	XMMATRIX mat = t.GetWorldMatrix();
	pSprite_->Draw(mat);
}

void TitleScene::Release()
{
}
