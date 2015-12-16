#include "Button.hpp"

namespace sf{
	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Text text) :
		position(position),
		size(size),
		normalColor(color),
		text(text)
	{
		state = sf::ButtonState::NORMAL;
		borderColor = color;
		borderColor.r = (borderColor.r * 1.3 <= 255) ? borderColor.r * 1.3 : 255;
		borderColor.g = (borderColor.g * 1.3 <= 255) ? borderColor.g * 1.3 : 255;
		borderColor.b = (borderColor.b * 1.3 <= 255) ? borderColor.b * 1.3 : 255;
		borderColor.r = (borderColor.r == 0) ? 63 : borderColor.r;
		borderColor.g = (borderColor.g == 0) ? 63 : borderColor.g;
		borderColor.b = (borderColor.b == 0) ? 63 : borderColor.b;
		pressedColor = color;
		pressedColor.r *= 0.7;
		pressedColor.g *= 0.7;
		pressedColor.b *= 0.7;
		this->text.setPosition(position);
	}


	Button::~Button()
	{
	}

	void Button::setState(sf::ButtonState state){
		this->state = state;
	}

	bool Button::isPressed(){
		return (state == sf::ButtonState::PRESSED || state == sf::ButtonState::PRESSED_LIGHT);
	}

	bool Button::isPointerInside(sf::Vector2i pointer){
		return (pointer.x > position.x) && (pointer.x < position.x + size.x) && (pointer.y > position.y) && (pointer.y < position.y + size.y);
	}

	void Button::draw(sf::RenderTarget* target){
		sf::RectangleShape rect(size);
		rect.setPosition(position);
		rect.setOutlineThickness(5);

		switch (state){
		case sf::ButtonState::NORMAL:
			rect.setFillColor(normalColor);
			rect.setOutlineColor(normalColor);
			break;
		case sf::ButtonState::NORMAL_LIGHT:
			rect.setFillColor(normalColor);
			rect.setOutlineColor(borderColor);
			break;
		case sf::ButtonState::PRESSED:
			rect.setFillColor(pressedColor);
			rect.setOutlineColor(pressedColor);
			break;
		case sf::ButtonState::PRESSED_LIGHT:
			rect.setFillColor(pressedColor);
			rect.setOutlineColor(borderColor);
			break;
		}
		target->draw(rect);

		if (!text.getString().isEmpty()){
			int charS = 100;
			int margin = size.x * 0.005;
			bool ok = false;
			while (!ok && charS > 0){
				text.setCharacterSize(charS);
				sf::FloatRect r = text.getGlobalBounds();
				if (size.x > r.width + margin){
					ok = true;
				}
				charS--;
			}
			text.setPosition(position);

			sf::FloatRect r = text.getGlobalBounds();

			int offsetX = position.x - text.getGlobalBounds().left;
			int offsetY = position.y - text.getGlobalBounds().top;
			
			text.setPosition((position.x + offsetX) + (size.x - text.getGlobalBounds().width) / 2, (position.y + offsetY) + (size.y - text.getGlobalBounds().height)/2);

			target->draw(text);
		}
	}
}
