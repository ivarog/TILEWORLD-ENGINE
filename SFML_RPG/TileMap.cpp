#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSizeGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}

	this->map.clear();
}

TileMap::TileMap(float gridSize, float textureScale, unsigned width, unsigned height, std::string textureFile)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->textureScale = textureScale;
	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;
	this->maxSizeWorld.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorld.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = textureFile;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());

	for (size_t x = 0; x < this->maxSizeGrid.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());

		for (size_t y = 0; y < this->maxSizeGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}

		}
	}

	if (!this->tileSheet.loadFromFile(textureFile))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME"<< textureFile << "/n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool& collision, const short& type)
{
	if (x < this->maxSizeGrid.x && x >= 0 && y < this->maxSizeGrid.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, textureRect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSizeGrid.x && x >= 0 && y < this->maxSizeGrid.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::saveToFile(const std::string fileName)
{
	/*Saves the entiretilemap to a text-file
	* Format:
	* Size x y
	* gridSize
	* layers
	* textureFile
	* gridPos x y layer, textureRect x y, collision, type
	*/

		std::ofstream outFile;
		outFile.open(fileName);

		if (outFile.is_open())
		{
			outFile << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << "\n" 
				<< this->gridSizeU << "\n"
				<< this->layers << "\n"
				<< this->textureFile << "\n";

			for (size_t x = 0; x < this->maxSizeGrid.x; x++)
			{
				for (size_t y = 0; y < this->maxSizeGrid.y; y++)
				{
					for (size_t z = 0; z < this->layers; z++)
					{
						if(this->map[x][y][z])
							outFile << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
					}

				}
			}
		}
		else
		{
			std::cout << "ERROR::TILEMAP COULD NOT SEVE TO FILE::FILENAME: " << fileName << "\n";
		}

		outFile.close();
}

void TileMap::loadFromFile(const std::string fileName)
{
	std::ifstream inFile;
	inFile.open(fileName);

	if (inFile.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string textureFile = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		inFile >> size.x >> size.y >> gridSize >> layers >> textureFile;

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;
		this->textureFile = textureFile;

		this->map.resize(this->maxSizeGrid.x, std::vector<std::vector<Tile*>>());

		for (size_t x = 0; x < this->maxSizeGrid.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t y = 0; y < this->maxSizeGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeGrid.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}

			}
		}

		if (!this->tileSheet.loadFromFile(textureFile))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME" << textureFile << "/n";

		//Load all tiles
		while (inFile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU / this->textureScale, this->gridSizeU / this->textureScale), collision, type);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP CPULD NOT SEVE TO FILE::FILENAME: " << fileName << "\n";
	}

	inFile.close();
}

void TileMap::updateCollision(Entity* entity)
{
	// WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorld.x)
	{
		entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	this->fromX = entity->getGridPosition(this->gridSizeU).x - 2;
	
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX >= this->maxSizeGrid.x)
		this->fromX = this->maxSizeGrid.x - 1;

	this->toX = entity->getGridPosition(this->gridSizeU).x + 1;

	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX >= this->maxSizeGrid.x)
		this->toX = this->maxSizeGrid.x - 1;

	this->fromY = entity->getGridPosition(this->gridSizeU).y - 2;

	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY >= this->maxSizeGrid.y)
		this->fromY = this->maxSizeGrid.y - 1;

	this->toY = entity->getGridPosition(this->gridSizeU).y + 1;

	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY >= this->maxSizeGrid.y)
		this->toY = this->maxSizeGrid.y - 1;

	/*if(this->)
	for (size_t x = fromX; x < this->toX; x++)
	{
		for (size_t y = fromY; y < this->toY; y++)
		{
			
		}
	}*/
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
				{
					z->render(target);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

