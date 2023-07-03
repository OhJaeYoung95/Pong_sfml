#include "stdafx.h"
#include "Ball.h"
#include "Utils.h"

Ball::Ball(const std::string n)
	: GameObject(n), speed(0.f), direction({0.f, 0.f})
{
}

Ball::~Ball()
{
}

const sf::Vector2f& Ball::GetPos() const
{
	return position;
}

void Ball::SetPos(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(position);
}

sf::FloatRect Ball::GetBounds() const
{
	return shape.getGlobalBounds();
}

void Ball::Init()
{
	shape.setRadius(10.f);
	Utils::SetOrigin(shape, Origins::BC);
	shape.setFillColor(sf::Color::White);
	SetPos({ 1280 * 0.5f, 720.f - 25.f });
	speed = 0.f;
	direction = { 0.f, 0.f };
}

void Ball::Release()
{
}

void Ball::Reset()
{
}

void Ball::Fire(sf::Vector2f dir, float s)
{
	direction = dir;
	speed = s;
}

void Ball::Update(float dt)
{
	SetPos(position + direction * speed * dt);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::SetPosition(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(p);
}

void Ball::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	shape.setPosition(position);
}

void Ball::SetOrigin(Origins origin)
{
	Utils::SetOrigin(shape, origin);

	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(shape, origin);
	}
}

void Ball::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	shape.setOrigin(x, y);
}

void Ball::OnCollisionTop()
{
	direction.y = abs(direction.y);
}

void Ball::OnCollisionBottom()
{
	direction.y = -abs(direction.y);
}

void Ball::OnCollisionLeft()
{
	direction.x = abs(direction.x);
}

void Ball::OnCollisionRight()
{
	direction.x = -abs(direction.x);
}
