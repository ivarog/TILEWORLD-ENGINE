#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Pixeled.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void SettingsState::initGUI()
{
	this->buttons["BACK"] = new GUI::Button(300.f, 550.f, 250.f, 50.f, &this->font, "Back", 12, sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["APPLY"] = new GUI::Button(800.f, 550.f, 250.f, 50.f, &this->font, "Apply", 12, sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	std::vector<std::string> modesStr;
	for (auto& i : this->modes)
	{
		modesStr.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	this->dropDownsList["RESOLUTION"] = new GUI::DropdownList(700, 300, 200, 50, font, modesStr.data(), modesStr.size()); 
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("Resolution \nFullscreen \nVsync \nAntialiasing");
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownsList.begin();
	for (it2 = this->dropDownsList.begin(); it2 != dropDownsList.end(); ++it2)
	{
		delete it2->second;
	}
}

void SettingsState::updateInput(const float& dt)
{
	//this->checkForQuit();	
}

void SettingsState::updateGUI(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		std::cout << this->dropDownsList["RESOLUTION"]->getActiveElementId();
		this->window->create(this->modes[this->dropDownsList["RESOLUTION"]->getActiveElementId()], "Test", sf::Style::Default);
	}

	for (auto& it : this->dropDownsList)
	{
		it.second->update(this->mousePosView, dt);
	} 
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGUI(dt);
}

void SettingsState::renderGUI(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto it : this->dropDownsList)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderGUI(*target);

	target->draw(this->optionsText);

}
