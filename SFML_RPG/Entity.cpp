#include "stdafx.h"
#include "Entity.h"
 
void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}


Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(std::map<std::string, sf::Texture>& textures)
{
	this->animationComponent = new AnimationComponent(this->sprite, textures);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offsetX, offsetY, width, height);
}


//Functions
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);
	}
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
