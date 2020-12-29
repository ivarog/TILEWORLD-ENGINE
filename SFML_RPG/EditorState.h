#pragma once

#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class EditorState :
    public State
{
private:
	//Variables
	sf::Font font;
	PauseMenu* pmenu;

	std::map<std::string, GUI::Button*> buttons;
	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initGUI();
	void initButtons();
	void initTilemap();
public:

	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Functions

	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGUI();
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

