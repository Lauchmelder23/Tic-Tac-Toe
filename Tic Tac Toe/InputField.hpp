#pragma once

#include <SFML/Graphics.hpp>

class InputField
{
public:
	InputField();
	~InputField();

	void Type(char letter);
	std::string Enter();
	void Backspace();

	void Render(sf::RenderWindow& target);

private:
	void updateText();

	std::string value;

	sf::Text info;
	sf::Text input;
	sf::Font* font;

	sf::RectangleShape field;
};

