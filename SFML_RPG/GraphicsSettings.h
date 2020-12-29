#pragma once
class GraphicsSettings
{
public:
	GraphicsSettings();

	std::string title;
	sf::VideoMode resolution;
	bool fullScreen;
	bool verticalSync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

