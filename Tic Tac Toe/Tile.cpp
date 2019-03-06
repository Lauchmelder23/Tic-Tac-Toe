#include "Tile.hpp"

#include <iostream>

Tile::Tile()
{
}

Tile::Tile(int posX, int posY)
{
	size = sf::Vector2f(200, 200);
	active = false;

	position = sf::Vector2f(posX, posY);

	frame.setFillColor(sf::Color::Black);
	frame.setOutlineThickness(-5);
	frame.setOutlineColor(sf::Color::Green);
	frame.setSize(size);
	frame.setPosition(position);
}


Tile::~Tile()
{
}

bool Tile::isClicked(int mouseX, int mouseY)
{
	if (mouseX > position.x && mouseX < position.x + size.x && mouseY > position.y && mouseY < position.y + size.y)
		return true;

	return false;
}

void Tile::Render(sf::RenderWindow& target)
{
	// target.draw(frame);
}



Cross::Cross()
{

}

Cross::Cross(int posX, int posY) :
	Tile(posX, posY)
{
	for (int i = 0; i < 2; i++)
	{
		lines[i].setFillColor(sf::Color(255, 50, 50));
		lines[i].setSize(sf::Vector2f(180, 10));
		lines[i].setOrigin(sf::Vector2f(lines[i].getGlobalBounds().left + lines[i].getLocalBounds().width / 2,
			lines[i].getGlobalBounds().top + lines[i].getLocalBounds().height / 2));
		lines[i].setPosition(posX + 100, posY + 100);
		
	}

	lines[0].rotate(45);
	lines[1].rotate(-45);
}

void Cross::Render(sf::RenderWindow& target)
{
	Tile::Render(target);

	target.draw(lines[0]);
	target.draw(lines[1]);
}







Circle::Circle()
{

}

Circle::Circle(int posX, int posY) :
	Tile(posX, posY)
{
	cir.setRadius(90);
	cir.setOutlineThickness(-10);
	cir.setOutlineColor(sf::Color(10, 10, 255));
	cir.setOrigin(sf::Vector2f(cir.getGlobalBounds().left + cir.getLocalBounds().width / 2,
		cir.getGlobalBounds().top + cir.getLocalBounds().height / 2));
	cir.setPosition(posX + 100, posY + 100);
	cir.setFillColor(sf::Color::Black);
}

void Circle::Render(sf::RenderWindow& target)
{
	Tile::Render(target);

	target.draw(cir);
}