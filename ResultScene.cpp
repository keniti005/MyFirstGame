#include "ResultScene.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"
#include "Engine/SceneManeger.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent,"ResultScene")
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	pSprite_ = new Sprite("assets\\Result.png");
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		MessageBoxA(0, "タイトルシーンに遷移します", "シーン遷移", MB_OK);
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_TITLE);
	}
}

void ResultScene::Draw()
{
	Transform t;
	t.scale_ = { 0.5f,0.5f,1.0f };
	t.Calculation();
	XMMATRIX mat = t.GetWorldMatrix();
	pSprite_->Draw(mat);
}

void ResultScene::Release()
{
}
