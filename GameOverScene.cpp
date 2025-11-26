#include "GameOverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"

GameOverScene::GameOverScene(GameObject* parent)
	:GameObject(parent,"GameOverScene")
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	if (Input::IsKeyDown(DIK_M))
	{
		MessageBoxA(0, "ゲームオーバー画面だよ", "GameOver", MB_OK);
	}
	if (Input::IsKeyDown(DIK_T))
	{
		MessageBoxA(0, "テストシーンに移動します", "シーン遷移", MB_OK);
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_TEST);
	}
}

void GameOverScene::Draw()
{
}

void GameOverScene::Release()
{
}
