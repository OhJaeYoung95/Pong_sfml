#pragma once
#include "GameObject.h"
class SpriteGo : public GameObject
{
public:
	sf::Sprite sprite;

	SpriteGo(const std::string n = "");
	virtual ~SpriteGo() override;

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;


};

