#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	//Accesors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);


	//Functions
	bool intersects(const sf::FloatRect& fRect);

	void update();
	void render(sf::RenderTarget& target);
};

