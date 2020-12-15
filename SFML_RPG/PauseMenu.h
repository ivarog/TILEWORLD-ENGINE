#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

#include "Button.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

