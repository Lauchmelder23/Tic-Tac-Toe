#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Field
{
public:
	Field();

	void Render(sf::RenderWindow& target);
	char Update();
	bool Click(int mouseX, int mouseY, char turn);

private:
	sf::RectangleShape lines[4];
	Tile* tiles[9];
};

