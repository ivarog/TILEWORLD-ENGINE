#pragma once

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	float textureScale;
	sf::Vector2u maxSizeGrid;
	sf::Vector2f maxSizeWorld;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	//Culling
	unsigned fromX;
	unsigned toX;
	unsigned fromY;
	unsigned toY;
	unsigned layer;

	void clear();

public:
	TileMap(float gridSize, float textureScale, unsigned width, unsigned height, std::string textureFile);
	~TileMap();

	const sf::Texture* getTileSheet() const;

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);

	void updateCollision(Entity* entity);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);
};
