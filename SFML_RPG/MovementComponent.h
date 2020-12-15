#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

enum MovementState { IdleDown, IdleLeft, IdleRight, IdleUp, Idle, Moving, WalkingLeft, WalkingRight, WalkingUp, WalkingDown };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	//Initializer functions
public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accesors
	const float& getMaxVelocity();
	const sf::Vector2f& getVelocity() const;
	MovementState playerState = IdleDown;

	//Functions
	const bool getState(const short unsigned state) const;

	void update(const float& dt);
	void move(const float dir_x, const float dir_y, const float& dt);


};

