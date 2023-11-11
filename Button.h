#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Button : public sf::Drawable, public sf::Transformable
{
public:
	
	Button(const std::string, const int, sf::Font&, const sf::RectangleShape);
	Button(const std::string&, const int, sf::Font&, sf::Texture*, const sf::IntRect&);
	//text, id, font, rectangleBase, texture, textureRect
	Button(const std::string&, const int, sf::Font&, const sf::RectangleShape&, sf::Texture*, const sf::IntRect&);
	Button(const std::string&, const int, sf::Font&, const int, sf::Texture*, const sf::IntRect&);
	//text, id, font, rectangleBase, fontSize, texture, textRect
	Button(const std::string&, const int, sf::Font&, const sf::RectangleShape&, const int, sf::Texture*, const sf::IntRect&);
	~Button();

	sf::FloatRect getBounds();
	int getValue();
	void setColor(sf::Color);
	void setSpriteScale(double, double);
	void setPosition(int, int);
private:
	sf::RectangleShape base;
	sf::Sprite sprite;
	sf::Font* font;
	sf::Text label;
	int value;

	float labelOffsetX;
	float labelOffsetY;

	float spriteOffsetX;
	float spriteOffsetY;

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};
