#pragma once

#include "Tile.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;

	void clear();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile);
	~TileMap();

	const sf::Texture* getTileSheet() const;

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);

	void update();
	void render(sf::RenderTarget& target);
};
