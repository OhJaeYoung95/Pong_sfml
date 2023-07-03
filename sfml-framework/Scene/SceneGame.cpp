#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "Ball.h"
#include "Bat.h"
#include <sstream>

SceneGame::SceneGame() : Scene(SceneId::Game), life(3), score(0), ballActive(false)
{
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();
	life = 3;
	score = 0;
	AddGo(new TextGo("Hud"));
	AddGo(new Bat("Bat"));
	AddGo(new Ball("Ball"));


	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();

	auto hud = (TextGo*)FindGo("Hud");
	hud->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	hud->text.setCharacterSize(50);
	hud->text.setFillColor(sf::Color::Blue);
	hud->text.setOutlineThickness(5);
	hud->text.setOutlineColor(sf::Color::White);
	hud->text.setPosition(20, 20);
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	auto bat = (Bat*)FindGo("Bat");
	auto ball = (Ball*)FindGo("Ball");

	if (!ballActive && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		ballActive = true;
		ball->Fire(Utils::Normalize({ 1.f, -1.f }), 1000.f);
	}
	else if (ballActive && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		ballActive = false;
		ball->Init();
		//Wbat.Init();
	}


	if (!ballActive)
	{
		ball->SetPos(bat->GetPos());
	}
	sf::FloatRect ballRect = ball->GetBounds();
	if (ballRect.top < 0.f)
	{
		// 위
		ball->OnCollisionTop();
	}
	else if (ballRect.top + ballRect.height > 720.f)
	{
		// 아래
		ball->OnCollisionBottom();
		life--;

		ballActive = false;
		ball->Init();
		if (life == 0)
		{
			bat->Init();
			score = 0;
			life = 3;
		}
	}
	else if (ballRect.left < 0.f)
	{
		// 왼쪽
		ball->OnCollisionLeft();
	}
	else if (ballRect.left + ballRect.width > 1280.f)
	{
		// 오른쪽
		ball->OnCollisionRight();
	}

	if (ballRect.intersects(bat->GetBounds()) && ball->direction.y > 0)
	{
		ball->OnCollisionBottom();
		score++;
	}

	auto hud = (TextGo*)FindGo("Hud");
	std::stringstream ss;
	ss << "Score: " << score << "\tLife: " << life;
	hud->text.setString(ss.str());
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
