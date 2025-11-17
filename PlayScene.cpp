#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_O))
	{
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
