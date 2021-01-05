#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned gridX, unsigned gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texrect, bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(gridX) * gridSizeF,static_cast<float>(gridY) * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texrect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
