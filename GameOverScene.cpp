#include "GameOverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"
#include "Engine/Sprite.h"

GameOverScene::GameOverScene(GameObject* parent)
	:GameObject(parent,"GameOverScene")
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	pSprite = new Sprite();
	pSprite->Initialize();
}

void GameOverScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_TEST);
	}
}

void GameOverScene::Draw()
{
	XMMATRIX mat = XMMatrixIdentity();
	pSprite->Draw(mat);
}

void GameOverScene::Release()
{
	pSprite->Release();
}
