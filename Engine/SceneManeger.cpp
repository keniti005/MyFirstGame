#include "SceneManeger.h"
#include "../PlayScene.h"
#include "../TestScene.h"
#include "../GameOverScene.h"
#include "Direct3D.h"

SceneManeger::SceneManeger(GameObject* parent)
	:GameObject(parent,"SceneManeger")
{
}

SceneManeger::~SceneManeger()
{
}

void SceneManeger::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManeger::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		//ƒV[ƒ“Ø‚è‘Ö‚¦ˆ—
		auto scene = childList_.front();
		scene->ReleaseSub();
		SAFE_DELETE(scene);
		childList_.clear();
		

		switch (nextSceneID_)
		{
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_GAMEOVER:
			Instantiate<GameOverScene>(this);
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManeger::Draw()
{
}

void SceneManeger::Release()
{
}

void SceneManeger::ChangeScene(SCENE_ID _nextScene)
{
	nextSceneID_ = _nextScene;
}
