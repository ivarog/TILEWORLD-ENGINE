#pragma once
#include <iostream>
#include <string>
#include <map>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;


		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height) : sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer), timer(0.f), done(false), width(width), height(height)
		{
			this->startRect = sf::Rect(startFrameX * width, startFrameY * height, width, height);
			this->currentRect = startRect;
			this->endRect = sf::Rect(framesX * width, framesY * height, width, height);
			
			this->sprite.setTexture(this->textureSheet);
			this->sprite.setTextureRect(this->startRect);
		}

		const bool& isDone() const
		{
			return this->done;
		}

		const bool& play(const float& dt)
		{
			this->done = false;
			//Update timer
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//Reset timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}

			return this->done;
		}

		const bool& play(const float& dt, float modPercent)
		{
			//Update timer
			this->done = false;
			if (modPercent < 0.5f) modPercent = 0.5f;
			this->timer += modPercent * 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//Reset timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			
			return this->done;

		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	std::map<std::string, Animation*> animations;
	std::map<std::string, sf::Texture> textures;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>& textures);
	virtual ~AnimationComponent();

	//Accesors
	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(const std::string key, sf::Texture& textureSheet, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority = false);


};

