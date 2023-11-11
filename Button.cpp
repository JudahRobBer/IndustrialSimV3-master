#include "Button.h"
#include <string>
#include <iostream>


Button::Button(const std::string labelText, const int initValue, sf::Font& f, const sf::RectangleShape rect)
{
	font = &f;

	// Initialize label
	label.setString(labelText);
	label.setFillColor(sf::Color::Black);
	label.setLetterSpacing(1.1);


	label.setFont(*font);
	label.setCharacterSize(36);

	// Initialize value
	value = initValue;

	base = rect;


	// Center the label
	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX - 20, labelY - (.25 * base.getSize().y));
}

// Constructor, applies default values to sf::RectangleShape base
Button::Button(const std::string& labelText, const int initValue, sf::Font& f, sf::Texture* txt, const sf::IntRect& rect)
{
	font = &f;

	// Initialize label
	label.setString(labelText);
	label.setFillColor(sf::Color::Black);
	label.setLetterSpacing(1.1);



	label.setFont(*font);
	label.setCharacterSize(48);

	// Initialize value
	value = initValue;

	// Initialize base
	base.setFillColor(sf::Color::White);
	base.setSize(sf::Vector2f(400.f, 50.f));
	base.setOutlineColor(sf::Color::Black);
	base.setOutlineThickness(10);


	// right Center the label
	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.25 * base.getSize().y));


	//assign texture
	sprite.setTexture(*txt);
	sprite.setTextureRect(rect);

	sf::FloatRect spriteSize = sprite.getLocalBounds();
	float spriteX = base.getPosition().x + ((base.getSize().x - spriteSize.width)  / 2);
	float spriteY = base.getPosition().y + ((base.getSize().y - spriteSize.height) / 2);

	sprite.setPosition(labelX, labelY - (.25 * base.getSize().y));
	

}

// Constructor for customizing sf::RectangleShape base
//PRIMARY USE CASE CONSTRUCTOR
Button::Button(const std::string& labelText, const int initValue, sf::Font& f, const sf::RectangleShape& initRect, sf::Texture* txt, const sf::IntRect& rect)
	: Button(labelText, initValue, f, txt, rect)
{
	// Initialize base
	base = initRect;

	// Recenter the label
	sf::FloatRect labelSize = label.getLocalBounds();
	labelOffsetX = base.getPosition().x + ((base.getSize().x - labelSize.width) * .75);
	labelOffsetY = base.getPosition().y + (base.getSize().y * .40);

	label.setPosition(labelOffsetX, labelOffsetY - (.25 * base.getSize().y));



	//assign texture
	sprite.setTexture(*txt);
	sprite.setTextureRect(rect);

	sf::FloatRect spriteSize = sprite.getLocalBounds();
	float spriteX = base.getPosition().x + (base.getSize().x * .05);
	float spriteY = base.getPosition().y + (base.getSize().y * .4);

	sprite.setPosition(spriteX, spriteY - (.25 * base.getSize().y));
	sprite.setScale(.2, .2);
}
	

Button::Button(const std::string& labelText, const int initValue, sf::Font& f, const int fontSize, sf::Texture* txt, const sf::IntRect& rect) :
	Button(labelText, initValue, f,txt, rect)
{
	label.setCharacterSize(fontSize);

	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.25 * base.getSize().y));
}

Button::Button(const std::string& labelText, const int initValue, sf::Font& f, const sf::RectangleShape& initRect, const int fontSize, sf::Texture* txt, const sf::IntRect& rect) : 
	Button(labelText, initValue, f, initRect, txt,rect)
{
	label.setCharacterSize(fontSize);

	sf::FloatRect labelSize = label.getLocalBounds();
	float labelX = base.getPosition().x + ((base.getSize().x - labelSize.width) / 2);
	float labelY = base.getPosition().y + ((base.getSize().y - labelSize.height) / 2);

	label.setPosition(labelX, labelY - (.33 * base.getSize().y));
}

Button::~Button()
{

}

// Gets called by window.draw(MenuButton)
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();

	target.draw(base, states);
	target.draw(label, states);
	target.draw(sprite, states);
	
}

// Returns a FloatRect containing base, used to detect clicks
sf::FloatRect Button::getBounds()
{
	return getTransform().transformRect(base.getGlobalBounds());
}

// Returns the button's value
int Button::getValue()
{
	return value;
}

void Button::setColor(sf::Color color)
{
	base.setFillColor(color);
}

void Button::setSpriteScale(double xFactor, double yFactor)
{
	sprite.setScale(sprite.getScale().x * xFactor, sprite.getScale().y * yFactor);
}

void Button::setPosition(int x, int y)
{
	base.setPosition(sf::Vector2f(x,y));

	//Recenter the Label
	labelOffsetX = base.getPosition().x + ((base.getSize().x - label.getLocalBounds().width) * .75);
	labelOffsetY = base.getPosition().y + (base.getSize().y * .40);
	label.setPosition(labelOffsetX, labelOffsetY - (.25 * base.getSize().y));

	//Recenter the Sprite
	spriteOffsetX = base.getPosition().x + (base.getSize().x * .05);
	spriteOffsetY = base.getPosition().y + (base.getSize().y * .4);
	sprite.setPosition(spriteOffsetX, spriteOffsetY - (.25 * base.getSize().y));
}
