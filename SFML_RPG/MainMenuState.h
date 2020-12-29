#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "GUI.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, GUI::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

