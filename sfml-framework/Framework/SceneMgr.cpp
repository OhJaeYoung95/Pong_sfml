#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneTitile.h"
#include "SceneGame.h"

void SceneMgr::ChangeScene(SceneId id)
{
	scenes[(int)currentSceneId]->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		return;
	}
			
	scenes.push_back(new SceneTitile());
	scenes.push_back(new SceneGame());

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::Update(float dt)
{
	scenes[(int)currentSceneId]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentSceneId]->Draw(window);
}
