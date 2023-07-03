#include "stdafx.h"
#include "SceneTitile.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "Framework.h"

SceneTitile::SceneTitile() : Scene(SceneId::Title)
{
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

SceneTitile::~SceneTitile()
{
}

void SceneTitile::Init()
{
	Release();
	
	AddGo(new SpriteGo("Text"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitile::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}

}

void SceneTitile::Enter()
{
	Scene::Enter();

	SpriteGo* findGo = (SpriteGo*)FindGo("Cloud");
	findGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/cloud.png"));

	sf::Vector2f centerPos = FRAMEWORK.GetWindowSize();
	centerPos.x *= 0.5f;
	centerPos.y *= 0.5f;

	findGo->SetPosition(centerPos);
	findGo->SetOrigin(Origins::MC);
}

void SceneTitile::Exit()
{
	Scene::Exit();
}

void SceneTitile::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}
}

void SceneTitile::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
