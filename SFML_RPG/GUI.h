#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace GUI
{
	class Button
	{
	private:
	
		short unsigned buttonState = BTN_ACTIVE;
		short unsigned id;
	
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height, 
			sf::Font* font, std::string text, unsigned characterSize, 
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, 
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
			sf::Color outlineIdleColor =  sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent, 
			short unsigned id = 0);
		virtual ~Button();

		//Accesors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);
	 
		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropdownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		GUI::Button* activeElement;
		std::vector<GUI::Button*> list;
		bool showList;


	public:
		DropdownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex = 0);
		~DropdownList();

		//Accesors
		const unsigned short& getActiveElementId() const;

		//Functions
		bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		float keytime;
		float keytimeMax;
		float gridSize;
		float textureScale;
		bool active;
		bool hidden;
		GUI::Button* hideBtn;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;


	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const float textureScale, const sf::Texture* textureSheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accesors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
