#pragma once

enum TileTypes
{
	DEFAULT = 0,
	DAMAGING,

};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(unsigned gridX, unsigned gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texrect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

