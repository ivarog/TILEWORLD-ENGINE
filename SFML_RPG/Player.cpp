#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
}


//Constructor destructor
Player::Player(float x, float y, std::map<std::string, sf::Texture>& textures)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 16.f, 16.f);
	this->createMovementComponent(80.f, 5.f, 3.f);
	this->createAnimationComponent(textures);

	this->animationComponent->addAnimation("ATTACK", textures["PLAYER_ATTACK_DOWN"], 10.f, 0, 0, 5, 0, 23, 23);
	this->animationComponent->addAnimation("IDLE_LEFT", textures["PLAYER_IDLE_LEFT"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("IDLE_RIGHT", textures["PLAYER_IDLE_RIGHT"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("IDLE_UP", textures["PLAYER_IDLE_UP"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("IDLE_DOWN", textures["PLAYER_IDLE_DOWN"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("WALK_LEFT", textures["PLAYER_WALK_LEFT"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("WALK_RIGHT", textures["PLAYER_WALK_RIGHT"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("WALK_UP", textures["PLAYER_WALK_UP"], 10.f, 0, 0, 5, 0, 16, 16);
	this->animationComponent->addAnimation("WALK_DOWN", textures["PLAYER_WALK_DOWN"], 10.f, 0, 0, 5, 0, 16, 16);


}

Player::~Player()
{
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}
	 if (this->movementComponent->getState(Idle))
	{
		if (this->movementComponent->playerState == WalkingDown || this->movementComponent->playerState == IdleDown)
		{
			this->animationComponent->play("IDLE_DOWN", dt);
			this->movementComponent->playerState = IdleDown;
		}
		else if (this->movementComponent->playerState == WalkingLeft || this->movementComponent->playerState == IdleLeft)
		{
			this->animationComponent->play("IDLE_LEFT", dt);
			this->movementComponent->playerState = IdleLeft;
		}
		else if (this->movementComponent->playerState == WalkingRight || this->movementComponent->playerState == IdleRight)
		{
			this->animationComponent->play("IDLE_RIGHT", dt);
			this->movementComponent->playerState = IdleRight;
		}
		else if (this->movementComponent->playerState == WalkingUp || this->movementComponent->playerState == IdleUp)
		{
			this->animationComponent->play("IDLE_UP", dt);
			this->movementComponent->playerState = IdleUp;
		}

	}
	else if (this->movementComponent->getState(WalkingLeft))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		this->movementComponent->playerState = WalkingLeft;
	}
	else if (this->movementComponent->getState(WalkingRight))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		this->movementComponent->playerState = WalkingRight;
	}
	else if (this->movementComponent->getState(WalkingUp))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		this->movementComponent->playerState = WalkingUp;
	}
	else if (this->movementComponent->getState(WalkingDown))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		this->movementComponent->playerState = WalkingDown;
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	

	this->hitboxComponent->update();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}

