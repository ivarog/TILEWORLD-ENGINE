#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	
	StateData() {};

	//Variables
	float gridSize;
	float textureScale;
	sf::RenderWindow* window; 
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys; 
	std::stack<State*>* states;

};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;
	float gridSize;
	float textureScale;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;
	//Functions
	virtual void initKeybinds() = 0; 

public:
	State(StateData* stateData);
	virtual ~State();

	//Accesors
	const bool & getQuit() const;
	const bool getKeyTime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

