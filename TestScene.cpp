#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	//スペースキー押したら
	//SceneManeger::ChangeScene(SCENE_ID_PLAY);を呼び出す
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManeger* pSceneManeger = (SceneManeger*)FindObjectByName("SceneManeger");
		pSceneManeger->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
