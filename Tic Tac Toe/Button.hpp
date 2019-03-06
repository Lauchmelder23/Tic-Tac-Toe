#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Util.h"

struct ColorPalette
{
	ColorPalette() {}
	ColorPalette(sf::Color _frame, sf::Color _background, sf::Color _label)
	{
		frame = _frame;
		background = _background;
		label = _label;
	}

	sf::Color frame, background, label;
};

class Button
{
public:
	Button() {}
	Button(std::string text, int x, int y);

	void Update(int mouseX, int mouseY);
	void Render(sf::RenderWindow& target);

	bool isClicked(int mouseX, int mouseY);
	void disable() {
		isDisabled = true;
	}
	void enable()
	{
		isDisabled = false;
	}

private:
	sf::RectangleShape background;
	sf::Text label;
	sf::Font* font;

	ColorPalette default, hover, clicked, disabled;

	bool isDisabled;
};