#include "Button.hpp"


Button::Button(std::string text, int x, int y)
{
	default = ColorPalette(sf::Color(70, 70, 70), sf::Color(130, 130, 130), sf::Color(255, 255, 255));
	hover = ColorPalette(sf::Color(70, 70, 70), sf::Color(160, 160, 160), sf::Color(255, 255, 255));
	clicked = ColorPalette(sf::Color(130, 130, 130), sf::Color(70, 70, 70), sf::Color(255, 255, 255));
	disabled = ColorPalette(sf::Color(10, 10, 10), sf::Color(40, 40, 40), sf::Color(120, 120, 120));

	background.setFillColor(default.background);
	background.setOutlineColor(default.frame);
	background.setOutlineThickness(15);
	background.setSize(sf::Vector2f(400, 150));
	background.setPosition(sf::Vector2f(x, y));

	font = new sf::Font();
	font->loadFromFile("C:/Windows/Fonts/lucon.ttf");

	label.setFont(*font);
	label.setColor(default.label);
	label.setCharacterSize(48);
	label.setString(text);
	label.setOrigin(sf::Vector2f(label.getLocalBounds().width / 2, label.getLocalBounds().height));
	label.setPosition(sf::Vector2f(background.getGlobalBounds().left + background.getLocalBounds().width / 2,
		background.getGlobalBounds().top + background.getLocalBounds().height / 2));

	isDisabled = false;
}

void Button::Update(int mouseX, int mouseY)
{
	if (mouseX > background.getGlobalBounds().left && mouseX < background.getGlobalBounds().left + background.getLocalBounds().width &&
		mouseY > background.getGlobalBounds().top && mouseY < background.getGlobalBounds().top + background.getLocalBounds().height)
	{
		background.setFillColor(hover.background);
		background.setOutlineColor(hover.frame);
		label.setFillColor(hover.label);

	}

	else
	{
		background.setFillColor(default.background);
		background.setOutlineColor(default.frame);
		label.setFillColor(default.label);
	}

	if (isDisabled)
	{
		background.setFillColor(disabled.background);
		background.setOutlineColor(disabled.frame);
		label.setFillColor(disabled.label);
	}
}

void Button::Render(sf::RenderWindow& target)
{
	target.draw(background);
	target.draw(label);
}

bool Button::isClicked(int mouseX, int mouseY)
{
	if (isDisabled) return false;

	if (mouseX > background.getGlobalBounds().left && mouseX < background.getGlobalBounds().left + background.getLocalBounds().width &&
		mouseY > background.getGlobalBounds().top && mouseY < background.getGlobalBounds().top + background.getLocalBounds().height)
	{
		background.setFillColor(default.background);
		background.setOutlineColor(default.frame);
		label.setFillColor(default.label);

		return true;
	}

	return false;
}
