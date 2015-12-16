#pragma once

#include "SFML\Graphics.hpp"
#include "Components.hpp"

namespace sf{
	class Button
	{
	public:
		Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Text text = sf::Text());
		~Button();
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::ButtonState state;
		sf::Color normalColor;
		sf::Color borderColor;
		sf::Color pressedColor;
		sf::Text text;
	public:
		void setState(sf::ButtonState state);
		bool isPressed();
		bool isPointerInside(sf::Vector2i pointer);
		void draw(sf::RenderTarget* target);
	};
}
