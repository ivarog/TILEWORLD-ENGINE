#include "stdafx.h"
#include "GUI.h"

GUI::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;

	this->id = id;
}

GUI::Button::~Button()
{
}

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const std::string GUI::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& GUI::Button::getId() const
{
	return this->id;
}

void GUI::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void GUI::Button::setId(const short unsigned id)
{
	this->id = id; 
}


void GUI::Button::update(const sf::Vector2f& mousePos)
{
	this->buttonState = BTN_IDLE;
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//DRPDOWN List

GUI::DropdownList::DropdownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex)
	: font(font), showList(false), keytimeMax(3.f), keytime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);
	this->activeElement = new GUI::Button(x, y, width, height, &this->font, list[defaultIndex], 12, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(new GUI::Button(x, y + (i + 1) * height, width, height, &this->font, list[i], 12, sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 200), sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), i));
	}

	
}

GUI::DropdownList::~DropdownList()
{
	delete this->activeElement;
	for (size_t i = 0; i > this->list.size(); i++)
	{
		delete this->list[i];
	}
}

const unsigned short& GUI::DropdownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

bool GUI::DropdownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void GUI::DropdownList::updateKeytime(const float &dt)
{
	if (this->keytime < keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void GUI::DropdownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		this->showList = showList ? false : true;
	}

	if (this->showList)
	{
		for (auto& i : this->list) 
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void GUI::DropdownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
