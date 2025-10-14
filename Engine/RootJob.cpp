#include "RootJob.h"
#include "../PlayScene.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	//PlaySceneを生成して、子オブジェクトに追加する

	//PlayScene* pPlayScene;
	//pPlayScene = new PlayScene(this);
	//pPlayScene->Initialize();
	//childList_.push_back(pPlayScene);
	Instantiate<PlayScene>(this);
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
