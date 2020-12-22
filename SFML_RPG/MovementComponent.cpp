#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration) 
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::getMaxVelocity()
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case Idle:
		return (this->velocity.x == 0.f && this->velocity.y == 0.f);
		break;
	case Moving:
		return (this->velocity.x != 0.f || this->velocity.y != 0.f);
		break;
	case WalkingLeft:
		return (this->velocity.x < 0.f);
		break;
	case WalkingRight:
		return (this->velocity.x > 0.f);
		break;
	case WalkingUp:
		return (this->velocity.y < 0.f);
		break;
	case WalkingDown:
		return (this->velocity.y > 0.f);
		break;
	}
	return false;
}


//Functions
void MovementComponent::update(const float& dt)
{
	velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
	velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);

	if (this->velocity.x > 0.f)
	{
		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)
	{
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f) this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)
	{
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)  this->velocity.y = 0.f;
	}

	//Final Move
	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}
