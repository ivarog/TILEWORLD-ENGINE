#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& fRect);

	void update();
	void render(sf::RenderTarget& target);
};

