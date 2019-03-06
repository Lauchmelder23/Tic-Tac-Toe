#include "InputField.hpp"



InputField::InputField()
{
	value = "";

	font = new sf::Font();
	font->loadFromFile("C:/Windows/Fonts/lucon.ttf");

	field.setFillColor(sf::Color(10, 10, 10));
	field.setOutlineThickness(5);
	field.setOutlineColor(sf::Color(60, 60, 60));
	field.setSize(sf::Vector2f(450, 50));
	field.setPosition(sf::Vector2f(250, 350));

	input.setFont(*font);
	input.setString(value);
	input.setCharacterSize(32);
	input.setPosition(sf::Vector2f(260, 350));

	info.setFont(*font);
	info.setString("Enter IP:");
	info.setCharacterSize(32);
	info.setPosition(sf::Vector2f(50, 350));
}


InputField::~InputField()
{
}

void InputField::updateText()
{
	input.setString(value);
}

void InputField::Type(char letter)
{
	value += letter;
	updateText();
}

std::string InputField::Enter()
{
	return value;
}

void InputField::Backspace()
{
	if(value != "")
		value.pop_back();

	updateText();
}

void InputField::Render(sf::RenderWindow& target)
{
	target.draw(field);
	target.draw(input);
	target.draw(info);
}
