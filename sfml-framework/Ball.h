#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
protected:
	sf::CircleShape shape;
	//sf::Vector2f position;

	float speed;

public:
	sf::Vector2f direction;

	Ball(const std::string n = "");
	virtual ~Ball() override;

	const sf::Vector2f& GetPos() const;
	void SetPos(const sf::Vector2f& pos);

	sf::FloatRect GetBounds() const;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	void Fire(sf::Vector2f dir, float s);

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);


	void OnCollisionTop();
	void OnCollisionBottom();
	void OnCollisionLeft();
	void OnCollisionRight();
};

