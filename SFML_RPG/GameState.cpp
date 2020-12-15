#include "GameState.h"


//Initializer functions

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Pixeled.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
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
	if (!this->textures["PLAYER_IDLE_LEFT"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Idle/Char_idle_left.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_RIGHT"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Idle/Char_idle_right.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_UP"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Idle/Char_idle_up.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_IDLE_DOWN"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Idle/Char_idle_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if(!this->textures["PLAYER_WALK_LEFT"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Walk/Char_walk_left.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_RIGHT"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Walk/Char_walk_right.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_UP"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Walk/Char_walk_up.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_WALK_DOWN"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Walk/Char_walk_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["PLAYER_ATTACK_DOWN"].loadFromFile("Resources/Tiny Adventure Pack Plus/Character/Char_one/Attack/Sword/Char_atk_down.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures);
}

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();

	//sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(300.f, 200.f));
	//window->setView(view);
}


GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
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

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else //Paused update
	{
		this->pmenu->update();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	
	this->player->render(*target);

	if (this->paused)
	{
		this->pmenu->render(*target);
	}
}