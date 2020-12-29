#include "stdafx.h"
#include "State.h"


State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->quit = false;
	this->paused = false;
	this->states = stateData->states;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = stateData->gridSize;
}


State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}


void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
	);
}

void State::updateKeytime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 30.f * dt;
}


