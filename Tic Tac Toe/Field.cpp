#include "Field.hpp"

#include <iostream>

Field::Field()
{
	tiles[0] = new Tile(50, 50);
	tiles[1] = new Tile(300, 50);
	tiles[2] = new Tile(550, 50);
	tiles[3] = new Tile(50, 300);
	tiles[4] = new Tile(300, 300);
	tiles[5] = new Tile(550, 300);
	tiles[6] = new Tile(50, 550);
	tiles[7] = new Tile(300, 550);
	tiles[8] = new Tile(550, 550);

	for (int i = 0; i < 4; i++)
	{
		lines[i].setFillColor(sf::Color(170, 170, 170));
	}

	lines[0].setPosition(250, 50);
	lines[0].setSize(sf::Vector2f(50, 700));

	lines[1].setPosition(500, 50);
	lines[1].setSize(sf::Vector2f(50, 700));

	lines[2].setPosition(50, 250);
	lines[2].setSize(sf::Vector2f(700, 50));

	lines[3].setPosition(50, 500);
	lines[3].setSize(sf::Vector2f(700, 50));
}

char Field::Update()
{
	if (tiles[0]->what() == 'x' && tiles[1]->what() == 'x' && tiles[2]->what() == 'x')
		return 'x';
	if (tiles[0]->what() == 'o' && tiles[1]->what() == 'o' && tiles[2]->what() == 'o')
		return 'o';

	if (tiles[3]->what() == 'x' && tiles[4]->what() == 'x' && tiles[5]->what() == 'x')
		return 'x';
	if (tiles[3]->what() == 'o' && tiles[4]->what() == 'o' && tiles[5]->what() == 'o')
		return 'o';

	if (tiles[6]->what() == 'x' && tiles[7]->what() == 'x' && tiles[8]->what() == 'x')
		return 'x';
	if (tiles[6]->what() == 'o' && tiles[7]->what() == 'o' && tiles[8]->what() == 'o')
		return 'o';




	if (tiles[0]->what() == 'x' && tiles[3]->what() == 'x' && tiles[6]->what() == 'x')
		return 'x';
	if (tiles[0]->what() == 'o' && tiles[3]->what() == 'o' && tiles[6]->what() == 'o')
		return 'o';

	if (tiles[1]->what() == 'x' && tiles[4]->what() == 'x' && tiles[7]->what() == 'x')
		return 'x';
	if (tiles[1]->what() == 'o' && tiles[4]->what() == 'o' && tiles[7]->what() == 'o')
		return 'o';

	if (tiles[2]->what() == 'x' && tiles[5]->what() == 'x' && tiles[8]->what() == 'x')
		return 'x';
	if (tiles[2]->what() == 'o' && tiles[5]->what() == 'o' && tiles[8]->what() == 'o')
		return 'o';




	if (tiles[0]->what() == 'x' && tiles[4]->what() == 'x' && tiles[8]->what() == 'x')
		return 'x';
	if (tiles[0]->what() == 'o' && tiles[4]->what() == 'o' && tiles[8]->what() == 'o')
		return 'o';

	if (tiles[2]->what() == 'x' && tiles[4]->what() == 'x' && tiles[6]->what() == 'x')
		return 'x';
	if (tiles[2]->what() == 'o' && tiles[4]->what() == 'o' && tiles[6]->what() == 'o')
		return 'o';

	bool tied = true;
	for (int i = 0; i < 9; i++)
		if (tiles[i]->what() == ' ')
			tied = false;

	if (tied) return 't';

	return ' ';
}


bool Field::Click(int mouseX, int mouseY, char turn)
{
	for (int i = 0; i < 9; i++)
	{
		if (tiles[i]->what() == ' ')
		{
			if (tiles[i]->isClicked(mouseX, mouseY))
			{
				//printf("Clicked Tile %i", i);

				sf::Vector2f pos = tiles[i]->getPosition();
				if (turn == 'x')
					tiles[i] = new Cross(pos.x, pos.y);
				else
					tiles[i] = new Circle(pos.x, pos.y);

				return true;
			}
		}
		//else {
		//	std::cout << "Mein Schwanz hurtet" << std::endl;
		//}
	}

	return false;
}

void Field::Render(sf::RenderWindow& target)
{
	for (int i = 0; i < 4; i++)
		target.draw(lines[i]);

	for (int i = 0; i < 9; i++)
		tiles[i]->Render(target);

	// std::cout << std::endl;
}