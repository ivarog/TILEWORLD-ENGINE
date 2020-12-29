#pragma once
#include "State.h"
#include "GUI.h"

class SettingsState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, GUI::Button*> buttons;
	std::map<std::string, GUI::DropdownList*> dropDownsList;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initText();

public:
    SettingsState(StateData* stateData);
    virtual ~SettingsState();

	void updateInput(const float& dt);
	void updateGUI(const float& dt);
	void update(const float& dt);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

