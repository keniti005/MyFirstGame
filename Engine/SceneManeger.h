#pragma once
#include "GameObject.h"

enum SCENE_ID
{
	SCENE_ID_TEST,
	SCENE_ID_PLAY,
	SCENE_ID_MAX
};

class SceneManeger : 
	public GameObject
{
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
public:
	SceneManeger(GameObject* parent);
	~SceneManeger();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ChangeScene(SCENE_ID _nextScene);
};