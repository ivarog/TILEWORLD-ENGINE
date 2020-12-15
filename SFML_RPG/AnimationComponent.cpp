#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>& textures)
	:sprite(sprite), textures(textures), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}


//Accesors
const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

void AnimationComponent::addAnimation(const std::string key, sf::Texture& textureSheet, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, textureSheet, animationTimer, startFrameX, startFrameY, framesX, framesY, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{

	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{

				this->sprite.setTexture(animations[key]->textureSheet);
				this->sprite.setTextureRect(animations[key]->startRect);

				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			
			//If the priority animation is done remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			};
		}
	}
	else //PLay animation if no other animation is set
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			this->sprite.setTexture(animations[key]->textureSheet);
			this->sprite.setTextureRect(animations[key]->startRect);

			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				this->sprite.setTexture(animations[key]->textureSheet);
				this->sprite.setTextureRect(animations[key]->startRect);

				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done remove it
			if (this->animations[key]->play(dt, abs(modifier / modifierMax)))
			{
				this->priorityAnimation = NULL;
			};
		
		}
	}
	else //PLay animation if no other animation is set
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			this->sprite.setTexture(animations[key]->textureSheet);
			this->sprite.setTextureRect(animations[key]->startRect);

			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifierMax));
	}

	return this->animations[key]->isDone();

}

//jorge galicia