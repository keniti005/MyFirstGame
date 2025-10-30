#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManeger.h"
#include "Engine/Model.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
	hModel_ = Model::Load("Hammer.fbx");
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	transform_.rotate_.y += 0.8f;
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
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestScene::Release()
{
}
