#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
protected:
	int life;
	int score;
	bool ballActive = false;
public:
	SceneGame();
	virtual ~SceneGame() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

