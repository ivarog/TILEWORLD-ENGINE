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
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texrect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

