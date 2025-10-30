#include "RootJob.h"
#include "../PlayScene.h"
#include "SceneManeger.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	Instantiate<SceneManeger>(this);
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
