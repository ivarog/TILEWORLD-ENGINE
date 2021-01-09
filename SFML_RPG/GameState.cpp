#include "stdafx.h"
#include "GameState.h"


//Initializer functions

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Pixeled.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(370.f, 220.f));
	this->view.setCenter(player->getPosition());
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE_LEFT"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Idle/Char_idle_left.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_RIGHT"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Idle/Char_idle_right.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_UP"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Idle/Char_idle_up.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_DOWN"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Idle/Char_idle_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if(!this->textures["PLAYER_WALK_LEFT"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Walk/Char_walk_left.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_RIGHT"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Walk/Char_walk_right.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_UP"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Walk/Char_walk_up.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_DOWN"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Walk/Char_walk_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_ATTACK_DOWN"].loadFromFile("Resources/Tiny_Adventure_Pack_Plus/Character/Char_one/Attack/Sword/Char_atk_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, this->stateData->textureScale, 10, 10, "Resources/Tiny_Adventure_Pack_Plus/Tilesets/TS_Dirt.png");
	this->tileMap->loadFromFile("text.mp");
}

//Constructors / Destructors
GameState::GameState(StateData* stateData) : State(stateData)
{
	this->initDeferredRender();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initView();
	this->initTileMap();

	//sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
	//window->setView(view);
}


GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
	//this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);

		this->player->update(dt);
		this->updateTileMap(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target);

	this->player->render(*target);

	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}

	//this->renderTexture.clear();
	//this->renderTexture.setView(this->view);
	//this->tileMap->render(this->renderTexture);

	//this->player->render(this->renderTexture);

	//if (this->paused)
	//{
	//	this->renderTexture.setView(this->renderTexture.getDefaultView());
	//	this->pmenu->render(this->renderTexture);
	//}

	////FINAL RENDER
	//this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	//target->draw(this->renderSprite);
}
