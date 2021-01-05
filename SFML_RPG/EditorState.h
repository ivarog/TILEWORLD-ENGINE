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
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, GUI::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	GUI::TextureSelector* textureSelector;

	bool collision;
	short type;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
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
	void updateGUI(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

