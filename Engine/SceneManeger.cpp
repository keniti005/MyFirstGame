#include "SceneManeger.h"
#include "../PlayScene.h"
#include "../TitleScene.h"
#include "../ResultScene.h"
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
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
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
		case SCENE_ID_TITLE:
			Instantiate<TitleScene>(this);
			break;
		case SCENE_ID_RESULT:
			Instantiate<ResultScene>(this);
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
