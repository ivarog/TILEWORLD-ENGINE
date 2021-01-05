#include "stdafx.h"
#include "Game.h"

//Static functions

//Initilizer functions

//Contructors destructors

void Game::initWindow()
{
	if(this->gSettings.fullScreen)
		this->window = new sf::RenderWindow(
			this->gSettings.resolution,
			this->gSettings.title,
			sf::Style::Fullscreen,
			this->gSettings.contextSettings);
	else
	this->window = new sf::RenderWindow(
		this->gSettings.resolution,
		this->gSettings.title,
		sf::Style::Titlebar | sf::Style::Close,
		this->gSettings.contextSettings
	);

	this->window->setFramerateLimit(this->gSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.verticalSync);
}

void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;

	// Original size tile = 16
	this->gridSize = 80.f;
	this->textureScale = 5.f;
}

void Game::initGraphicsSettings()
{
	this->gSettings.loadFromFile("Config/graphics.ini");
}

void Game::initSateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
	this->stateData.textureScale = this->textureScale;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "/n";
	}
}

Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initSateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions

void Game::endApplication()
{
	std::cout << "Ending application" << std::endl;
}

void Game::updateDt()
{
	/*Updates thr dt variables with the time it takes to update and render one frame*/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		
		if (this->states.top()->getQuit())
		{ 
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//Render items
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
