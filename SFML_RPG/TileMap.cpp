#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
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
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = textureFile;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}

		}
	}

	if (!this->tileSheet.loadFromFile(textureFile))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME"<< textureFile << "/n";
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
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, textureRect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
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
			outFile << this->maxSize.x << " " << this->maxSize.y << "\n" 
				<< this->gridSizeU << "\n"
				<< this->layers << "\n"
				<< this->textureFile << "\n";

			for (size_t x = 0; x < this->maxSize.x; x++)
			{
				for (size_t y = 0; y < this->maxSize.y; y++)
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
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = textureFile;

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

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

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z != NULL)
					z->render(target);
			}
		}
	}
}

