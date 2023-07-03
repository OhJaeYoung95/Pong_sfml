#pragma once
#include "GameObject.h"
class Bat : public GameObject
{
protected:
	float speed = 1000.f;
	sf::Vector2f direction;

	//sf::Vector2f position;
	sf::RectangleShape shape;

public:
	Bat(const std::string n = "");
	virtual ~Bat() override;

	const sf::Vector2f& GetPos() const;
	void SetPos(const sf::Vector2f& pos);

	sf::FloatRect GetBounds() const;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

};

