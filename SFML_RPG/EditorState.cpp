#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(32, 0, 16, 16);
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Pixeled.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT", 500.f, "Quit");
}

void EditorState::initGUI()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setFillColor(sf::Color::Transparent);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initButtons()
{

}

void EditorState::initTilemap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

EditorState::EditorState(StateData* stateData) : State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGUI();
	this->initTilemap();
}


EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	delete pmenu;
	delete this->tileMap;
}


void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeyTime())
	{
		if (this->textureRect.left < 80)
		{
			this->textureRect.left += 16;
		}
	}
}

void EditorState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGUI();
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);
	this->renderGUI(*target);

	this->tileMap->render(*target);

	if (this->paused)
	{
		this->pmenu->render(*target);
	}

	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/

}